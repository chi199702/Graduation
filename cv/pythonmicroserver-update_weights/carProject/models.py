from carProject.utils.google_utils import *
from carProject.utils.layers import *
from carProject.utils.parse_config import *

ONNX_EXPORT = False


def create_modules(module_defs, img_size, cfg):
    # Constructs module list of layer blocks from module configuration in module_defs

    img_size = [img_size] * 2 if isinstance(img_size, int) else img_size  # expand if necessary
    _ = module_defs.pop(0)  # cfg training hyperparams (unused)
    output_filters = [3]  # input channels
    module_list = nn.ModuleList()
    routs = []  # list of layers which rout to deeper layers
    yolo_index = -1

    for i, mdef in enumerate(module_defs):
        modules = nn.Sequential()

        if mdef['type'] == 'convolutional':
            bn = mdef['batch_normalize']
            filters = mdef['filters']
            k = mdef['size']  # kernel size
            stride = mdef['stride'] if 'stride' in mdef else (mdef['stride_y'], mdef['stride_x'])
            if isinstance(k, int):  # single-size conv
                modules.add_module('Conv2d', nn.Conv2d(in_channels=output_filters[-1],
                                                       out_channels=filters,
                                                       kernel_size=k,
                                                       stride=stride,
                                                       padding=k // 2 if mdef['pad'] else 0,
                                                       groups=mdef['groups'] if 'groups' in mdef else 1,
                                                       bias=not bn))
            else:  # multiple-size conv
                modules.add_module('MixConv2d', MixConv2d(in_ch=output_filters[-1],
                                                          out_ch=filters,
                                                          k=k,
                                                          stride=stride,
                                                          bias=not bn))

            if bn:
                modules.add_module('BatchNorm2d', nn.BatchNorm2d(filters, momentum=0.03, eps=1E-4))
            else:
                routs.append(i)  # detection output (goes into yolo layer)

            if mdef['activation'] == 'leaky':
                modules.add_module('activation', nn.LeakyReLU(0.1, inplace=True))
            elif mdef['activation'] == 'swish':
                modules.add_module('activation', Swish())
            elif mdef['activation'] == 'mish':
                modules.add_module('activation', Mish())

        elif mdef['type'] == 'BatchNorm2d':
            filters = output_filters[-1]
            modules = nn.BatchNorm2d(filters, momentum=0.03, eps=1E-4)
            if i == 0 and filters == 3:  # normalize RGB image
                # imagenet mean and var https://pytorch.org/docs/stable/torchvision/models.html#classification
                modules.running_mean = torch.tensor([0.485, 0.456, 0.406])
                modules.running_var = torch.tensor([0.0524, 0.0502, 0.0506])

        elif mdef['type'] == 'maxpool':
            k = mdef['size']  # kernel size
            stride = mdef['stride']
            maxpool = nn.MaxPool2d(kernel_size=k, stride=stride, padding=(k - 1) // 2)
            if k == 2 and stride == 1:  # yolov3-tiny
                modules.add_module('ZeroPad2d', nn.ZeroPad2d((0, 1, 0, 1)))
                modules.add_module('MaxPool2d', maxpool)
            else:
                modules = maxpool

        elif mdef['type'] == 'upsample':
            if ONNX_EXPORT:  # explicitly state size, avoid scale_factor
                g = (yolo_index + 1) * 2 / 32  # gain
                modules = nn.Upsample(size=tuple(int(x * g) for x in img_size))  # img_size = (320, 192)
            else:
                modules = nn.Upsample(scale_factor=mdef['stride'])

        elif mdef['type'] == 'route':  # nn.Sequential() placeholder for 'route' layer
            layers = mdef['layers']
            filters = sum([output_filters[l + 1 if l > 0 else l] for l in layers])
            routs.extend([i + l if l < 0 else l for l in layers])
            modules = FeatureConcat(layers=layers)

        elif mdef['type'] == 'shortcut':  # nn.Sequential() placeholder for 'shortcut' layer
            layers = mdef['from']
            filters = output_filters[-1]
            routs.extend([i + l if l < 0 else l for l in layers])
            modules = WeightedFeatureFusion(layers=layers, weight='weights_type' in mdef)

        elif mdef['type'] == 'reorg3d':  # yolov3-spp-pan-scale
            pass

        elif mdef['type'] == 'yolo':
            yolo_index += 1
            stride = [32, 16, 8]  # P5, P4, P3 strides
            if any(x in cfg for x in ['panet', 'yolov4', 'cd53']):  # stride order reversed
                stride = list(reversed(stride))
            layers = mdef['from'] if 'from' in mdef else []
            modules = YOLOLayer(anchors=mdef['anchors'][mdef['mask']],  # anchor list
                                nc=mdef['classes'],  # number of classes
                                img_size=img_size,  # (416, 416)
                                yolo_index=yolo_index,  # 0, 1, 2...
                                layers=layers,  # output layers
                                stride=stride[yolo_index])

            # Initialize preceding Conv2d() bias (https://arxiv.org/pdf/1708.02002.pdf section 3.3)
            try:
                j = layers[yolo_index] if 'from' in mdef else -1
                bias_ = module_list[j][0].bias  # shape(255,)
                bias = bias_[:modules.no * modules.na].view(modules.na, -1)  # shape(3,85)
                bias[:, 4] += -4.5  # obj
                bias[:, 5:] += math.log(0.6 / (modules.nc - 0.99))  # cls (sigmoid(p) = 1/nc)
                module_list[j][0].bias = torch.nn.Parameter(bias_, requires_grad=bias_.requires_grad)
            except:
                print('WARNING: smart bias initialization failure.')

        else:
            print('Warning: Unrecognized Layer Type: ' + mdef['type'])

        # Register module list and number of output filters
        module_list.append(modules)
        output_filters.append(filters)

    routs_binary = [False] * (i + 1)
    for i in routs:
        routs_binary[i] = True
    return module_list, routs_binary


class YOLOLayer(nn.Module):
    def __init__(self, anchors, nc, img_size, yolo_index, layers, stride):
        super(YOLOLayer, self).__init__()
        self.anchors = torch.Tensor(anchors)
        self.index = yolo_index  # index of this layer in layers
        self.layers = layers  # model output layer indices
        self.stride = stride  # layer stride
        self.nl = len(layers)  # number of output layers (3)
        self.na = len(anchors)  # number of anchors (3)
        self.nc = nc  # number of classes (80)
        self.no = nc + 5  # number of outputs (85)
        self.nx, self.ny, self.ng = 0, 0, 0  # initialize number of x, y gridpoints
        self.anchor_vec = self.anchors / self.stride
        self.anchor_wh = self.anchor_vec.view(1, self.na, 1, 1, 2)

        if ONNX_EXPORT:
            self.training = False
            self.create_grids((img_size[1] // stride, img_size[0] // stride))  # number x, y grid points

    def create_grids(self, ng=(13, 13), device='cpu'):
        self.nx, self.ny = ng  # x and y grid size
        self.ng = torch.tensor(ng, dtype=torch.float)

        # build xy offsets
        if not self.training:
            yv, xv = torch.meshgrid([torch.arange(self.ny, device=device), torch.arange(self.nx, device=device)])
            self.grid = torch.stack((xv, yv), 2).view((1, 1, self.ny, self.nx, 2)).float()

        if self.anchor_vec.device != device:
            self.anchor_vec = self.anchor_vec.to(device)
            self.anchor_wh = self.anchor_wh.to(device)

    def forward(self, p, out):
        ASFF = False  # https://arxiv.org/abs/1911.09516
        if ASFF:
            i, n = self.index, self.nl  # index in layers, number of layers
            p = out[self.layers[i]]
            bs, _, ny, nx = p.shape  # bs, 255, 13, 13
            if (self.nx, self.ny) != (nx, ny):
                self.create_grids((nx, ny), p.device)

            # outputs and weights
            # w = F.softmax(p[:, -n:], 1)  # normalized weights
            w = torch.sigmoid(p[:, -n:]) * (2 / n)  # sigmoid weights (faster)
            # w = w / w.sum(1).unsqueeze(1)  # normalize across layer dimension

            # weighted ASFF sum
            p = out[self.layers[i]][:, :-n] * w[:, i:i + 1]
            for j in range(n):
                if j != i:
                    p += w[:, j:j + 1] * \
                         F.interpolate(out[self.layers[j]][:, :-n], size=[ny, nx], mode='bilinear', align_corners=False)

        elif ONNX_EXPORT:
            bs = 1  # batch size
        else:
            bs, _, ny, nx = p.shape  # bs, 255, 13, 13
            if (self.nx, self.ny) != (nx, ny):
                self.create_grids((nx, ny), p.device)

        # p.view(bs, 255, 13, 13) -- > (bs, 3, 13, 13, 85)  # (bs, anchors, grid, grid, classes + xywh)
        p = p.view(bs, self.na, self.no, self.ny, self.nx).permute(0, 1, 3, 4, 2).contiguous()  # prediction

        if self.training:
            return p

        elif ONNX_EXPORT:
            # Avoid broadcasting for ANE operations
            m = self.na * self.nx * self.ny
            ng = 1. / self.ng.repeat(m, 1)
            grid = self.grid.repeat(1, self.na, 1, 1, 1).view(m, 2)
            anchor_wh = self.anchor_wh.repeat(1, 1, self.nx, self.ny, 1).view(m, 2) * ng

            p = p.view(m, self.no)
            xy = torch.sigmoid(p[:, 0:2]) + grid  # x, y
            wh = torch.exp(p[:, 2:4]) * anchor_wh  # width, height
            p_cls = torch.sigmoid(p[:, 4:5]) if self.nc == 1 else \
                torch.sigmoid(p[:, 5:self.no]) * torch.sigmoid(p[:, 4:5])  # conf
            return p_cls, xy * ng, wh

        else:  # inference
            io = p.clone()  # inference output
            io[..., :2] = torch.sigmoid(io[..., :2]) + self.grid  # xy
            io[..., 2:4] = torch.exp(io[..., 2:4]) * self.anchor_wh  # wh yolo method
            io[..., :4] *= self.stride
            torch.sigmoid_(io[..., 4:])
            return io.view(bs, -1, self.no), p  # view [1, 3, 13, 13, 85] as [1, 507, 85]


class Darknet(nn.Module):
    # YOLOv3 object detection model

    def __init__(self, cfg, img_size=(416, 416), verbose=False):
        super(Darknet, self).__init__()

        self.module_defs = parse_model_cfg(cfg)
        self.module_list, self.routs = create_modules(self.module_defs, img_size, cfg)
        self.yolo_layers = get_yolo_layers(self)
        # torch_utils.initialize_weights(self)


        self.version = np.array([0, 2, 5], dtype=np.int32)  # (int32) version info: major, minor, revision
        self.seen = np.array([0], dtype=np.int64)  # (int64) number of images seen during training
        self.info(verbose) if not ONNX_EXPORT else None  # print model description

    def forward(self, x, augment=False, verbose=False):

        if not augment:
            return self.forward_once(x)
        else:
            img_size = x.shape[-2:]  # height, width
            s = [0.83, 0.67]  # scales
            y = []
            for i, xi in enumerate((x,
                                    torch_utils.scale_img(x.flip(3), s[0], same_shape=False),  # flip-lr and scale
                                    torch_utils.scale_img(x, s[1], same_shape=False),  # scale
                                    )):
                # cv2.imwrite('img%g.jpg' % i, 255 * xi[0].numpy().transpose((1, 2, 0))[:, :, ::-1])
                y.append(self.forward_once(xi)[0])

            y[1][..., :4] /= s[0]  # scale
            y[1][..., 0] = img_size[1] - y[1][..., 0]  # flip lr
            y[2][..., :4] /= s[1]  # scale

            # for i, yi in enumerate(y):  # coco small, medium, large = < 32**2 < 96**2 <
            #     area = yi[..., 2:4].prod(2)[:, :, None]
            #     if i == 1:
            #         yi *= (area < 96. ** 2).float()
            #     elif i == 2:
            #         yi *= (area > 32. ** 2).float()
            #     y[i] = yi

            y = torch.cat(y, 1)
            return y, None

    def forward_once(self, x, augment=False, verbose=False):
        img_size = x.shape[-2:]  # height, width
        yolo_out, out = [], []
        if verbose:
            print('0', x.shape)
            str = ''

        # Augment images (inference and test only)
        if augment:
            nb = x.shape[0]  # batch size
            s = [0.83, 0.67]  # scales
            x = torch.cat((x,
                           torch_utils.scale_img(x.flip(3), s[0]),  # flip-lr and scale
                           torch_utils.scale_img(x, s[1]),  # scale
                           ), 0)

        for i, module in enumerate(self.module_list):
            name = module.__class__.__name__
            if name in ['WeightedFeatureFusion', 'FeatureConcat']:  # sum, concat
                if verbose:
                    l = [i - 1] + module.layers  # layers
                    sh = [list(x.shape)] + [list(out[i].shape) for i in module.layers]  # shapes
                    str = ' >> ' + ' + '.join(['layer %g %s' % x for x in zip(l, sh)])
                x = module(x, out)  # WeightedFeatureFusion(), FeatureConcat()
            elif name == 'YOLOLayer':
                yolo_out.append(module(x, out))
            else:  # run module directly, i.e. mtype = 'convolutional', 'upsample', 'maxpool', 'batchnorm2d' etc.
                x = module(x)

            out.append(x if self.routs[i] else [])
            if verbose:
                print('%g/%g %s -' % (i, len(self.module_list), name), list(x.shape), str)
                str = ''

        if self.training:  # train
            return yolo_out
        elif ONNX_EXPORT:  # export
            x = [torch.cat(x, 0) for x in zip(*yolo_out)]
            return x[0], torch.cat(x[1:3], 1)  # scores, boxes: 3780x80, 3780x4
        else:  # inference or test
            x, p = zip(*yolo_out)  # inference output, training output
            x = torch.cat(x, 1)  # cat yolo outputs
            if augment:  # de-augment results
                x = torch.split(x, nb, dim=0)
                x[1][..., :4] /= s[0]  # scale
                x[1][..., 0] = img_size[1] - x[1][..., 0]  # flip lr
                x[2][..., :4] /= s[1]  # scale
                x = torch.cat(x, 1)
            return x, p

    def fuse(self):
        # Fuse Conv2d + BatchNorm2d layers throughout model
        print('Fusing layers...')
        fused_list = nn.ModuleList()
        for a in list(self.children())[0]:
            if isinstance(a, nn.Sequential):
                for i, b in enumerate(a):
                    if isinstance(b, nn.modules.batchnorm.BatchNorm2d):
                        # fuse this bn layer with the previous conv2d layer
                        conv = a[i - 1]
                        fused = torch_utils.fuse_conv_and_bn(conv, b)
                        a = nn.Sequential(fused, *list(a.children())[i + 1:])
                        break
            fused_list.append(a)
        self.module_list = fused_list
        self.info() if not ONNX_EXPORT else None  # yolov3-spp reduced from 225 to 152 layers

    def info(self, verbose=False):
        torch_utils.model_info(self, verbose)


def get_yolo_layers(model):
    return [i for i, m in enumerate(model.module_list) if m.__class__.__name__ == 'YOLOLayer']  # [89, 101, 113]


def load_darknet_weights(self, weights, cutoff=-1):
    # Parses and loads the weights stored in 'weights'

    # Establish cutoffs (load layers between 0 and cutoff. if cutoff = -1 all are loaded)
    file = Path(weights).name
    print(file)
    if file == 'darknet53.conv.74':
        cutoff = 75
    elif file == 'yolov3-tiny.conv.15':
        cutoff = 15

    # Read weights file
    with open(weights, 'rb') as f:


        self.version = np.fromfile(f, dtype=np.int32, count=3)  # (int32) version info: major, minor, revision
        self.seen = np.fromfile(f, dtype=np.int64, count=1)  # (int64) number of images seen during training

        weights = np.fromfile(f, dtype=np.float32)  # the rest are weights

    ptr = 0
    for i, (mdef, module) in enumerate(zip(self.module_defs[:cutoff], self.module_list[:cutoff])):
        if mdef['type'] == 'convolutional':
            conv = module[0]
            if mdef['batch_normalize']:
                # Load BN bias, weights, running mean and running variance
                bn = module[1]
                nb = bn.bias.numel()  # number of biases
                # Bias
                bn.bias.data.copy_(torch.from_numpy(weights[ptr:ptr + nb]).view_as(bn.bias))
                ptr += nb
                # Weight
                bn.weight.data.copy_(torch.from_numpy(weights[ptr:ptr + nb]).view_as(bn.weight))
                ptr += nb
                # Running Mean
                bn.running_mean.data.copy_(torch.from_numpy(weights[ptr:ptr + nb]).view_as(bn.running_mean))
                ptr += nb
                # Running Var
                bn.running_var.data.copy_(torch.from_numpy(weights[ptr:ptr + nb]).view_as(bn.running_var))
                ptr += nb
            else:
                # Load conv. bias
                nb = conv.bias.numel()
                conv_b = torch.from_numpy(weights[ptr:ptr + nb]).view_as(conv.bias)
                conv.bias.data.copy_(conv_b)
                ptr += nb
            # Load conv. weights
            nw = conv.weight.numel()  # number of weights
            conv.weight.data.copy_(torch.from_numpy(weights[ptr:ptr + nw]).view_as(conv.weight))
            ptr += nw


def save_weights(self, path='model.weights', cutoff=-1):
    # Converts a PyTorch model to Darket format (*.pt to *.weights)
    # Note: Does not work if model.fuse() is applied
    with open(path, 'wb') as f:

        self.version.tofile(f)  # (int32) version info: major, minor, revision
        self.seen.tofile(f)  # (int64) number of images seen during training

        # Iterate through layers
        for i, (mdef, module) in enumerate(zip(self.module_defs[:cutoff], self.module_list[:cutoff])):
            if mdef['type'] == 'convolutional':
                conv_layer = module[0]
                # If batch norm, load bn first
                if mdef['batch_normalize']:
                    bn_layer = module[1]
                    bn_layer.bias.data.cpu().numpy().tofile(f)
                    bn_layer.weight.data.cpu().numpy().tofile(f)
                    bn_layer.running_mean.data.cpu().numpy().tofile(f)
                    bn_layer.running_var.data.cpu().numpy().tofile(f)
                # Load conv bias
                else:
                    conv_layer.bias.data.cpu().numpy().tofile(f)
                # Load conv weights
                conv_layer.weight.data.cpu().numpy().tofile(f)


def convert(cfg='cfg/yolov3-spp.cfg', weights='weights/yolov3-spp.weights'):
    # Converts between PyTorch and Darknet format per extension (i.e. *.weights convert to *.pt and vice versa)
    # from models import *; convert('cfg/yolov3-spp.cfg', 'weights/yolov3-spp.weights')

    # Initialize model
    model = Darknet(cfg)

    # Load weights and save
    if weights.endswith('.pt'):  # if PyTorch format
        model.load_state_dict(torch.load(weights, map_location='cpu')['model'])
        target = weights.rsplit('.', 1)[0] + '.weights'
        save_weights(model, path=target, cutoff=-1)
        print("Success: converted '%s' to '%s'" % (weights, target))

    elif weights.endswith('.weights'):  # darknet format
        _ = load_darknet_weights(model, weights)

        chkpt = {'epoch': -1,
                 'best_fitness': None,
                 'training_results': None,
                 'model': model.state_dict(),
                 'optimizer': None}

        target = weights.rsplit('.', 1)[0] + '.pt'
        torch.save(chkpt, target)
        print("Success: converted '%s' to '%s'" % (weights, target))

    else:
        print('Error: extension not supported.')


def attempt_download(weights):
    # Attempt to download pretrained weights if not found locally
    weights = weights.strip()
    msg = weights + ' missing, try downloading from https://drive.google.com/open?id=1LezFG5g3BCW6iYaV89B2i64cqEUZD7e0'

    if len(weights) > 0 and not os.path.isfile(weights):
        d = {'yolov3-spp.weights': '16lYS4bcIdM2HdmyJBVDOvt3Trx6N3W2R',
             'yolov3.weights': '1uTlyDWlnaqXcsKOktP5aH_zRDbfcDp-y',
             'yolov3-tiny.weights': '1CCF-iNIIkYesIDzaPvdwlcf7H9zSsKZQ',
             'yolov3-spp.pt': '1f6Ovy3BSq2wYq4UfvFUpxJFNDFfrIDcR',
             'yolov3.pt': '1SHNFyoe5Ni8DajDNEqgB2oVKBb_NoEad',
             'yolov3-tiny.pt': '10m_3MlpQwRtZetQxtksm9jqHrPTHZ6vo',
             'darknet53.conv.74': '1WUVBid-XuoUBmvzBVUCBl_ELrzqwA8dJ',
             'yolov3-tiny.conv.15': '1Bw0kCpplxUqyRYAJr9RY9SGnOJbo9nEj',
             'yolov3-spp-ultralytics.pt': '1UcR-zVoMs7DH5dj3N1bswkiQTA4dmKF4'}

        file = Path(weights).name
        if file in d:
            r = gdrive_download(id=d[file], name=weights)
        else:  # download from pjreddie.com
            url = 'https://pjreddie.com/media/files/' + file
            print('Downloading ' + url)
            r = os.system('curl -f ' + url + ' -o ' + weights)

        # Error check
        if not (r == 0 and os.path.exists(weights) and os.path.getsize(weights) > 1E6):  # weights exist and > 1MB
            os.system('rm ' + weights)  # remove partial downloads
            raise Exception(msg)


#---------------
#   OCR Model
#---------------


class ConvBNRelu(nn.Module):
    """conv => BN => Relu(activate) (=> Pool => Dropout)"""

    def __init__(self, in_channel, out_channel, filter_kernel=3, stride=1, padding=0):
        super(ConvBNRelu, self).__init__()
        self.model = nn.Sequential(
            nn.Conv2d(in_channels=in_channel, out_channels=out_channel, kernel_size=filter_kernel, stride=stride,
                      padding=padding),
            nn.BatchNorm2d(out_channel),
            nn.ReLU(inplace=True),
        )

    def forward(self, x):
        x = self.model(x)
        return x


class stem(nn.Module):
    def __init__(self, in_channel, out_channel, filter_kernel=3, stride=2, padding=0):
        super(stem, self).__init__()
        # 4*3*36*136
        self.conv1 = ConvBNRelu(in_channel, out_channel=out_channel, filter_kernel=filter_kernel, stride=stride,
                                padding=padding)
        # 4*32*17*67
        self.conv2 = ConvBNRelu(out_channel, 32, 3, 1, 0)
        # 4*32*15*65
        self.conv3 = ConvBNRelu(32, 64, 3, 1, padding=1)
        # 4*64*15*65
        self.submodule1_pool = nn.MaxPool2d(kernel_size=3, stride=2, padding=0)
        # 4*64*7*32
        self.submodule1_conv = ConvBNRelu(64, 96, 3, 2, 0)
        # 4*96*7*32

        # 4*160*7*32
        self.submodule2_left_branch_conv1 = ConvBNRelu(160, 64, 1, 1, padding=0)
        # 4*160*7*32
        self.submodule2_left_branch_conv2 = ConvBNRelu(64, 96, 3, 1, padding=0)
        # 4*96*5*30
        # 4*160*7*32
        self.submodule2_right_branch_conv1 = ConvBNRelu(160, 64, 1, 1, 0)
        # 4*64*7*32
        self.submodule2_right_branch_conv2 = ConvBNRelu(64, 64, (1, 7), 1, padding=(0, 3))
        # 4*64*7*32
        self.submodule2_right_branch_conv3 = ConvBNRelu(64, 64, (7, 1), 1, padding=(3, 0))
        # 4*64*7*32
        self.submodule2_right_branch_conv4 = ConvBNRelu(64, 96, 3, 1, padding=0)
        # 4*96*5*30

        # 4*192*5*30
        self.submodule3_left_branch_conv1 = ConvBNRelu(192, 192, 3, 2, padding=0)
        # 4*192*2*14
        # 4*192*5*30
        self.submodule3_right_branch_pool = nn.MaxPool2d(kernel_size=3, stride=2, padding=0)
        # 4*192*2*14

    def forward(self, x):
        x = self.conv1(x)
        x = self.conv2(x)
        x = self.conv3(x)

        submodule1_x1 = self.submodule1_pool(x)
        submodule1_x2 = self.submodule1_conv(x)

        submodule1_x = [submodule1_x1, submodule1_x2]
        submodule1_x = torch.cat(submodule1_x, 1)

        submodule2_x1 = self.submodule2_left_branch_conv1(submodule1_x)
        submodule2_x1 = self.submodule2_left_branch_conv2(submodule2_x1)
        submodule2_x2 = self.submodule2_right_branch_conv1(submodule1_x)
        submodule2_x2 = self.submodule2_right_branch_conv2(submodule2_x2)
        submodule2_x2 = self.submodule2_right_branch_conv3(submodule2_x2)
        submodule2_x2 = self.submodule2_right_branch_conv4(submodule2_x2)

        submodule2_x = [submodule2_x1, submodule2_x2]
        submodule2_x = torch.cat(submodule2_x, 1)

        submodule3_x1 = self.submodule3_left_branch_conv1(submodule2_x)
        submodule3_x2 = self.submodule3_right_branch_pool(submodule2_x)

        submodule3_x = [submodule3_x1, submodule3_x2]
        return torch.cat(submodule3_x, 1)


class Inception_resnet_A_resnetblock(nn.Module):
    def __init__(self, in_channel, out_channel=32, filter_kernel=1, stride=1, padding=0):
        super(Inception_resnet_A_resnetblock, self).__init__()

        self.in_channel = in_channel

        self.out_channel = out_channel

        self.filter_kernel = filter_kernel

        self.stride = stride

        self.padding = padding
        # (384,32,1,1,0)
        # 4*384*2*14
        self.branch0_conv1 = ConvBNRelu(self.in_channel, self.out_channel, self.filter_kernel, self.stride,
                                        self.padding)
        # 4*32*2*14
        # 4*384*2*14
        self.branch1_conv1 = ConvBNRelu(self.in_channel, self.out_channel, self.filter_kernel, self.stride,
                                        self.padding)
        # 4*32*2*14
        self.branch1_conv2 = ConvBNRelu(32, 32, 3, 1, padding=1)
        # 4*32*2*14
        # 4*384*2*14
        self.branch2_conv1 = ConvBNRelu(self.in_channel, self.out_channel, self.filter_kernel, self.stride,
                                        self.padding)
        # 4*32*2*14
        self.branch2_conv2 = ConvBNRelu(32, 48, 3, 1, padding=1)
        # 4*48*2*14
        self.branch2_conv3 = ConvBNRelu(48, 64, 3, 1, padding=1)
        # 4*64*2*14

        # 4*128*2*14
        self.conv = nn.Conv2d(128, 384, 1, 1, padding=0)
        # 4*384*2*14
        self.batchnormalization = nn.BatchNorm2d(384)
        self.activation = nn.ReLU()

    def forward(self, input):
        residual = input

        branch1_x = self.branch0_conv1(input)

        branch2_x = self.branch1_conv1(input)
        branch2_x = self.branch1_conv2(branch2_x)

        branch3_x = self.branch2_conv1(input)
        branch3_x = self.branch2_conv2(branch3_x)
        branch3_x = self.branch2_conv3(branch3_x)

        x = [branch1_x, branch2_x, branch3_x]
        x = torch.cat(x, dim=1)

        x = self.conv(x)
        x = self.batchnormalization(x)

        out = self.activation(x + residual)

        return out


class Recduction_A(nn.Module):
    def __init__(self, in_channel):
        super(Recduction_A, self).__init__()

        self.in_channel = in_channel
        # (4,384,35,35)
        self.branch0_pool = nn.MaxPool2d(kernel_size=3, stride=2, padding=0)
        # 4*384*17*17
        # (4,384,35,35)
        self.branch1_conv1 = ConvBNRelu(self.in_channel, 384, 3, 2, 0)
        # 4*384*17*17
        # (4,384,35,35)
        self.branch2_conv1 = ConvBNRelu(self.in_channel, 256, 1, 1, 0)
        # 4*384*35*35
        self.branch2_conv2 = ConvBNRelu(256, 256, 3, 1, 1)
        # 4*384*35*35
        self.branch2_conv3 = ConvBNRelu(256, 384, 3, 2, 0)
        # 4*384*17*17

    def forward(self, x):
        x1 = self.branch0_pool(x)

        x2 = self.branch1_conv1(x)

        x3 = self.branch2_conv1(x)
        x3 = self.branch2_conv2(x3)
        x3 = self.branch2_conv3(x3)

        out = [x1, x2, x3]

        return torch.cat(out, dim=1)


class Inception_resnet_B_resnetblock(nn.Module):
    def __init__(self, in_channels):
        super(Inception_resnet_B_resnetblock, self).__init__()

        self.in_channels = in_channels
        # (4,1152,17,17)
        self.branch0_conv1 = ConvBNRelu(self.in_channels, 192, 1, 1, 0)
        # (4,192,17,17)
        # (4,1152,17,17)
        self.branch1_conv1 = ConvBNRelu(self.in_channels, 128, 1, 1, 0)
        # (4,128,17,17)
        self.branch1_conv2 = ConvBNRelu(128, 160, (1, 7), 1, (0, 3))
        # (4,160,17,17)
        self.branch1_conv3 = ConvBNRelu(160, 192, (7, 1), 1, (3, 0))
        # (4,192,17,17)

        # (4,384,17,17)
        self.conv = nn.Conv2d(384, 1152, 1, 1, 0)
        # (4,1152,17,17)
        self.batchnormalization = nn.BatchNorm2d(1152)
        self.activation = nn.ReLU()

    def forward(self, input):
        residual = input

        x1 = self.branch0_conv1(input)

        x2 = self.branch1_conv1(input)
        x2 = self.branch1_conv2(x2)
        x2 = self.branch1_conv3(x2)

        x = [x1, x2]
        x = torch.cat(x, dim=1)

        x = self.conv(x)
        x = self.batchnormalization(x)

        out = self.activation(x + residual)

        return out


class reduction_B(nn.Module):
    def __init__(self, in_channels):
        super(reduction_B, self).__init__()

        self.in_channels = in_channels
        # (4,1152,17,17)
        self.branch0_pool = nn.MaxPool2d(3, 2, padding=0)
        # (4,1152,8,8)
        # (4,1152,17,17)
        self.branch1_conv1 = ConvBNRelu(self.in_channels, 192, 1, 1, 0)
        # (4,192,17,17)
        self.branch1_conv2 = ConvBNRelu(192, 192, 3, 2, 0)
        # (4,192,8,8)
        # (4,1152,17,17)
        self.branch2_conv1 = ConvBNRelu(self.in_channels, 256, 1, 1, 0)
        # (4,256,17,17)
        self.branch2_conv2 = ConvBNRelu(256, 256, (1, 7), 1, (0, 3))
        # (4,256,17,17)
        self.branch2_conv3 = ConvBNRelu(256, 320, (7, 1), 1, (3, 0))
        # (4,320,17,17)
        self.branch2_conv4 = ConvBNRelu(320, 320, (3, 3), 2, 0)
        # (4,320,8,8)

    def forward(self, x):
        x1 = self.branch0_pool(x)

        x2 = self.branch1_conv1(x)
        x2 = self.branch1_conv2(x2)

        x3 = self.branch2_conv1(x)
        x3 = self.branch2_conv2(x3)
        x3 = self.branch2_conv3(x3)
        x3 = self.branch2_conv4(x3)

        x = [x1, x2, x3]

        x = torch.cat(x, dim=1)

        return x


class inception_resnet_c(nn.Module):
    def __init__(self, in_channels):
        super(inception_resnet_c, self).__init__()

        self.in_channels = in_channels
        # (4,1664,8,8)
        self.branch0_conv1 = ConvBNRelu(self.in_channels, 192, 1, 1, 0)
        # (4,192,8,8)

        # (4,1664,8,8)
        self.branch1_conv1 = ConvBNRelu(self.in_channels, 192, 1, 1, 0)
        # (4,192,8,8)
        self.branch1_conv2 = ConvBNRelu(192, 224, (1, 3), 1, (0, 1))
        # (4,224,8,8)
        self.branch1_conv3 = ConvBNRelu(224, 256, (3, 1), 1, (1, 0))
        # (4,256,8,8)

        # (4,448,8,8)
        self.conv = nn.Conv2d(448, 1664, 1, 1, padding=0)
        # (4,1664,8,8)
        self.batchnormalization = nn.BatchNorm2d(1664)
        self.activation = nn.ReLU()

    def forward(self, input):
        resdiual = input

        x1 = self.branch0_conv1(input)

        x2 = self.branch1_conv1(input)
        x2 = self.branch1_conv2(x2)
        x2 = self.branch1_conv3(x2)

        x = [x1, x2]
        x = torch.cat(x, dim=1)

        x = self.conv(x)
        x = self.batchnormalization(x)

        out = self.activation(x + resdiual)
        # print(out.shape)
        # [4,1664,8,8]
        return out


class inception_resnet_v2(nn.Module):
    def __init__(self, in_channels):
        super(inception_resnet_v2, self).__init__()
        self.stem_layer = stem(in_channels, 32, 3, 2, 0)
        self.resnetA_layer_list = nn.ModuleList([Inception_resnet_A_resnetblock(384, 32, 1, 1, 0) for _ in range(5)])
        self.dropout_layer = nn.Dropout(0.8)

        self.linear_layer = nn.Sequential(
            nn.Linear(384, 1024),
            nn.ReLU(),
        )

        self.linear_layer_length = nn.Linear(1024, 10)
        self.linear_layer_chinese = nn.Linear(1024, 83)
        self.linear_layer_car1 = nn.Linear(1024, 83)
        self.linear_layer_car2 = nn.Linear(1024, 83)
        self.linear_layer_car3 = nn.Linear(1024, 83)
        self.linear_layer_car4 = nn.Linear(1024, 83)
        self.linear_layer_car5 = nn.Linear(1024, 83)
        self.linear_layer_car6 = nn.Linear(1024, 83)
        self.linear_layer_car7 = nn.Linear(1024, 83)

    def forward(self, x):
        x = self.stem_layer(x)

        for layer in self.resnetA_layer_list:
            x = layer(x)

        x = F.adaptive_avg_pool2d(x, (1, 1))

        x = x.flatten(start_dim=1, end_dim=-1)

        x = self.dropout_layer(x)
        x = self.linear_layer(x)

        length = self.linear_layer_length(x)
        chinese_carplate = self.linear_layer_chinese(x)
        num1 = self.linear_layer_car1(x)
        num2 = self.linear_layer_car2(x)
        num3 = self.linear_layer_car3(x)
        num4 = self.linear_layer_car4(x)
        num5 = self.linear_layer_car5(x)
        num6 = self.linear_layer_car6(x)
        num7 = self.linear_layer_car7(x)

        return length, chinese_carplate, num1, num2, num3, num4, num5, num6, num7


from carProject.models import *  # set ONNX_EXPORT in models.py
from carProject.utils.datasets import *
from carProject.utils.utils import *
from torch.utils.data import DataLoader



class Detector:
    def __init__(self,opt):
        super(Detector, self).__init__()
        self.opt = opt_arguments()
        self.opt.batch_size = opt.batchSize
        if opt.GPU_MODE == "-1":
            self.opt.device = "cpu"
        else:
            self.opt.device=opt.GPU_MODE
        self.model,self.device ,self.half= self.init_model_and_gpu_env(self.opt)

    def init_model_and_gpu_env(self,opt = None):
        imgsz = (320, 192) if ONNX_EXPORT else opt.img_size  # (320, 192) or (416, 256) or (608, 352) for (height, width)
        weights, half = opt.weights, opt.half

        device = torch_utils.select_device(device='cpu' if ONNX_EXPORT else opt.device)
        model = Darknet(opt.cfg, imgsz)

        if weights.endswith('.pt'):  # pytorch format
            model.load_state_dict(torch.load(weights, map_location=device)['model'])
        else:  # darknet format
            load_darknet_weights(model, weights)

        model.to(device).eval()


        half = half and device.type != 'cpu'  # half precision only supported on CUDA
        if half:
            model.half()
        return model,device,half

    def detect_yolo(self,img_path):
        with torch.no_grad():
            cropped = self.detect(img_path,opt=self.opt)
        return cropped

    def detect(self,img_path = None,opt = None):

        dataset = LoadImages(img_path, img_size=(512,512))

        datasetLoader = DataLoader(
            dataset=dataset,
            batch_size=opt.batch_size,
            shuffle=False,
            num_workers=0,
        )

        for img, img_origin in datasetLoader:
            img = img.to(self.device)
            img = img.half() if self.half else img.float()  # uint8 to fp16/32
            img /= 255.0  # 0 - 255 to 0.0 - 1.0
            if img.ndimension() == 3:
                img = img.unsqueeze(0)

            # Inference
            # t1 = torch_utils.time_synchronized()
            pred = self.model(img, augment=opt.augment)[0]
            # t2 = torch_utils.time_synchronized()

            # to float
            if self.half:
                pred = pred.float()


            pred = non_max_suppression(pred, opt.conf_thres, opt.iou_thres,
                                    multi_label=False, classes=opt.classes, agnostic=opt.agnostic_nms)


            crop_axis_list = []
            conf = None
            img_cropped_list = []
            img_detect = []
            conf_list = []


            for i, det in enumerate(pred):  # detections for image i
                imgShape_temp = img_origin[i].shape
                if det is not None and len(det):
                # Rescale boxes from imgsz to img_origin size

                    det[:, :4] = scale_coords(img.shape[2:], det[:, :4], imgShape_temp).round()


                    xyxy = None
                    for *xyxy, conf, cls in det:
                        xyxy = xyxy
                        conf_list.append(conf.cpu().item())
                        #坐标cpu化以及item化(tensor->item)
                        crop_axis = [int(s.cpu().item()) for s in xyxy]
                        crop_axis_list.append(crop_axis)
                        img_cropped = img_origin[i][int(crop_axis[1]):int(crop_axis[3]),int(crop_axis[0]):int(crop_axis[2])]
                        img_cropped_list.append(img_cropped)

                    img_detect.append((conf_list,crop_axis_list,img_cropped_list))
                    crop_axis_list = []
                    img_cropped_list = []
                    conf_list = []

            if len(img_detect) == 0:
                return None
            else:
                return img_detect


#arguments options

class opt_arguments:
    def __init__(self):
        super(opt_arguments, self).__init__()
        self.cfg = r'cfg/yolov3-tiny.cfg'
        self.weights = 'weights/weights_best.pt'
        self.img_size = 512
        self.conf_thres = 0.4
        self.iou_thres = 0.8
        self.half = True
        self.device = '0' #'cpu'表示使用cpu模式 ,如果使用GPU模式，只需要写上你的GPU编号，比如有四块GPU，那么就写'0,1,2,3'
        self.batch_size = 1 #这里用来修改batchsize
        self.classes = None
        self.agnostic_nms = False
        self.augment = False




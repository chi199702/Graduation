import numpy as np
import os
import cv2
from carProject.models import inception_resnet_v2
from carProject.utils.ocr_utils import *
from torch.utils.data import DataLoader

import torch



class opt_arguments:
    def __init__(self):
        super(opt_arguments, self).__init__()
        self.parameters_path = r"weights/weights_best_ocr.pt"
        self.device = "0" #此处改为cpu，则启用cpu模式，如果改为GPU编号，比如"0",则使用编号为0的的GPU
        self.train_on_gpu_available = torch.cuda.is_available()

class recognition:
    def __init__(self,opt):
        super(recognition, self).__init__()
        self.opt = opt_arguments()
        if opt.GPU_MODE == "-1":
            self.opt.device = "cpu"
        else:
            self.opt.device = opt.GPU_MODE
        self.channels = 3
        self.device = None
        self.model = self.init_model_and_gpu_env(self.opt)
    def init_model_and_gpu_env(self,opt: opt_arguments = None):

        model = inception_resnet_v2(in_channels=self.channels)

        if self.opt.train_on_gpu_available and self.opt.device != "cpu":
            os.environ['CUDA_VISIBLE_DEVICES'] = self.opt.device
            c = 1024 ** 2  # bytes to MB
            ng = torch.cuda.device_count()
            x = [torch.cuda.get_device_properties(i) for i in range(ng)]
            s = 'OCR MOUDLE Using GPU '
            for i in range(0, ng):
                if i == 1:
                    s = ' ' * len(s)
                print("%sdevice%g _CudaDeviceProperties(name='%s', total_memory=%dMB)" %
                        (s, i, x[i].name, x[i].total_memory / c))
            self.device = torch.device("cuda:%s"%(0))
            model.cuda()
        else:
            self.device = torch.device("cpu")
            model.to(self.device)
            print("OCR MOUDLE Using CPU")

        if os.path.isfile(opt.parameters_path):
            if self.opt.device == "cpu":
                checkpoint = torch.load(self.opt.parameters_path,map_location=self.device)
            else:
                checkpoint = torch.load(self.opt.parameters_path, map_location=self.device)
            model.load_state_dict(checkpoint['model_state_dict'])
            return model
    def decode_char(self,image):
        outputs = None
        ocr_res = []
        ocrDataSet = OcrDataSet(image,get_test_augmentation())
        dataLoader = DataLoader(
            dataset=ocrDataSet,
            batch_size=len(image),
            shuffle=False,
            num_workers=0,
        )
        for i,data in enumerate(dataLoader):
            if self.opt.train_on_gpu_available and self.opt.device != "cpu":
                data = data.cuda()
            with torch.no_grad():
                self.model.eval()
                outputs = self.model(data)
        return decode(outputs,len(image))
        # ocr_res.append(decode(outputs,len(image)))

        # image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        # transform = get_test_augmentation()
        # augment = transform(image=image)
        # image = augment['image']
        # image = np.transpose(image, [2, 0, 1])
        # image = torch.from_numpy(image)
        # image = torch.unsqueeze(image, 0).float()
        # if self.opt.train_on_gpu_available and self.opt.device != "cpu":
        #     image = image.cuda()
        # with torch.no_grad():
        #     self.model.eval()
        #     outputs = self.model(image)
        # return ocr_res
        # return decode(outputs,image.size(0))






































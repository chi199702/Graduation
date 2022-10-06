import torch
import albumentations as albu
import torch.nn.functional as F
from torch.utils.data import Dataset
from torchvision import transforms
import cv2
import numpy as np

chars = [u"京", u"沪", u"津", u"渝", u"冀", u"晋", u"蒙", u"辽", u"吉", u"黑", u"苏", u"浙", u"皖", u"闽", u"赣", u"鲁", u"豫", u"鄂",
         u"湘", u"粤", u"桂",
         u"琼", u"川", u"贵", u"云", u"藏", u"陕", u"甘", u"青", u"宁", u"新", u"0", u"1", u"2", u"3", u"4", u"5", u"6", u"7",
         u"8", u"9", u"A",
         u"B", u"C", u"D", u"E", u"F", u"G", u"H", u"J", u"K", u"L", u"M", u"N", u"P", u"Q", u"R", u"S", u"T", u"U",
         u"V", u"W", u"X",
         u"Y", u"Z", u"港", u"学", u"使", u"警", u"澳", u"挂", u"军", u"北", u"南", u"广", u"沈", u"兰", u"成", u"济", u"海", u"民",
         u"航", u"空"
         ]
MAX_LENGTH = 1000
length_carPlate = [1, 2, 3, 4, 5, 6, 7, 8, 9, MAX_LENGTH]


def get_test_augmentation():
    test_transform = [
        albu.Normalize(mean=(0.485, 0.456, 0.406), std=(0.229, 0.224, 0.225), p=1)
    ]
    return albu.Compose(test_transform, p=1)

def decode(outputs,count):
    confidence = {}
    prediction_car_plate = ''
    pre_length_list = []
    prediction_car_plate_list = []
    
    #----------------------
    #提高速度二：carPlateRecognize(OCR)/carProject/utils/ocr_utils.py
    #这是一个返回 车牌中的 长度和各个位置从左往右数数的置信度的值，以字典的形式返回，如果不需要，可以注释掉
    #----------------------

    #-------注释开始--------------------------
    # length_confidence = {}
    # first_confidence = {}
    # second_confidence = {}
    # third_confidence = {}
    # fourth_confidence = {}
    # fifth_confidence = {}
    # six_confidence = {}
    # seventh_confidence = {}
    # eigth_confidence = {}
    #
    # length_proba = F.softmax(outputs[0],dim=1)
    # length_confidence["7"] = length_proba[0][6].cpu().item()
    # length_confidence["8"] = length_proba[0][7].cpu().item()
    # confidence["length"]   = length_confidence
    # for i in range(83):
    #     first_confidence[str(chars[i])]   = F.softmax(outputs[1],dim=1)[0][i].cpu().item()
    #     second_confidence[str(chars[i])]  = F.softmax(outputs[2],dim=1)[0][i].cpu().item()
    #     third_confidence[str(chars[i])]   = F.softmax(outputs[3],dim=1)[0][i].cpu().item()
    #     fourth_confidence[str(chars[i])]  = F.softmax(outputs[4],dim=1)[0][i].cpu().item()
    #     fifth_confidence[str(chars[i])]   = F.softmax(outputs[5],dim=1)[0][i].cpu().item()
    #     six_confidence[str(chars[i])]     = F.softmax(outputs[6],dim=1)[0][i].cpu().item()
    #     seventh_confidence[str(chars[i])] = F.softmax(outputs[7],dim=1)[0][i].cpu().item()
    #     eigth_confidence[str(chars[i])]   = F.softmax(outputs[8],dim=1)[0][i].cpu().item()
    # confidence["first_position"]  = first_confidence
    # confidence["second_position"] = second_confidence
    # confidence["third_position"]  = third_confidence
    # confidence["fourth_position"] = fourth_confidence
    # confidence["fifth_position"]  = fifth_confidence
    # confidence["six_position"]    = six_confidence
    # confidence["seven_position"]  = seventh_confidence
    # confidence["eigth_position"]  = eigth_confidence
    #--------------------注释结束的地方------------------

    for i in range(count):

        pre_length_list.append(length_carPlate[torch.max(outputs[0], 1)[1][i].item()])
        prediction_car_plate = prediction_car_plate + chars[torch.max(outputs[1], 1)[1][i].item()] + \
                               chars[torch.max(outputs[2], 1)[1][i].item()] + \
                               chars[torch.max(outputs[3], 1)[1][i].item()] + \
                               chars[torch.max(outputs[4], 1)[1][i].item()] + \
                               chars[torch.max(outputs[5], 1)[1][i].item()] + \
                               chars[torch.max(outputs[6], 1)[1][i].item()] + \
                               chars[torch.max(outputs[7], 1)[1][i].item()] + \
                               chars[torch.max(outputs[8], 1)[1][i].item()]
        prediction_car_plate_list.append(prediction_car_plate)
        prediction_car_plate = ""
    # print(prediction_car_plate_list)
    return prediction_car_plate_list
    # if prediction_car_plate_list[0][7] == chars[82]:
    #     prediction_car_plate_list[0] = prediction_car_plate_list[0][:7]
    #
    # return prediction_car_plate_list,confidence

class OcrDataSet(Dataset):
    def __init__(self,img_list=None,transforms = transforms.Compose([transforms.ToTensor()])):
        super(OcrDataSet, self).__init__()
        self.img_list = img_list
        self.transform = transforms
    def __len__(self):
        return len(self.img_list)
    def __getitem__(self, item_index):

        image = self.img_list[item_index]
        image = cv2.cvtColor(image,cv2.COLOR_BGR2RGB)

        if self.transform:
            augmented = self.transform(image = image)
            image = augmented['image']
        image = np.transpose(image,[2,0,1])
        image = torch.from_numpy(image)

        return image

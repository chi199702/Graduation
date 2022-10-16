#车牌识别所需package
from licenseplate import *

import argparse
import json
import numpy as np
import cv2
import os
from PIL import Image, ImageDraw, ImageFont

# -*- coding: utf-8 -*-
# @Author  : wdk
# @Time    : 2020/10/20
# @Function: python flask算法微服务
# @version2.0

#第一次运行的时候随便加载当前目录中的一张图片们可以进行“预热”

################
#修改为你自己的路径
################

rootDir = "../photos"
saved_path = r"../p_results"

parser = argparse.ArgumentParser()
parser.add_argument("--GPU_MODE",type=str,default=str(0),help="input -1,0,1,2,3 etc")
parser.add_argument("--port",type=int,default=5000,help="input port")
parser.add_argument("--batchSize",type=int,default=1,help="input batchSize")
opt = parser.parse_args()


def cv2ImgAddText(img, text, left, top, textColor=(255, 0, 0), textSize=20):
    if (isinstance(img, np.ndarray)):  # 判断是否OpenCV图片类型
        img = Image.fromarray(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    # 创建一个可以在给定图像上绘图的对象
    draw = ImageDraw.Draw(img)
    # 字体的格式
    fontStyle = ImageFont.truetype(
        "font/simsun.ttc", textSize, encoding="utf-8")
    # 绘制文本
    draw.text((left, top), text, textColor, font=fontStyle)
    # 转换回OpenCV格式
    return cv2.cvtColor(np.asarray(img), cv2.COLOR_RGB2BGR)

PR = LPR(os.path.join(os.path.join(os.path.split(os.path.realpath(__file__))[0],"licenseplate"),"models"),opt)
def HyperLPR_plate_recognition(Input_BGR):
    return PR.plate_recognition(Input_BGR)

# if __name__ == '__main__':
#     videoCapture = cv2.VideoCapture(r"/home/user/cwm/video/00001.MTS")
#     count = 0
#     img_list = None
#     success, frame = videoCapture.read()
#     fps = 0
#     res = 0
#     while success:
#         fps = fps + 1
#         img_list = []
#         img_list.append(frame)
#         infor = HyperLPR_plate_recognition(img_list)
#         if infor:
#             res += 1
#             for i, (iret_conf, iret_box, iret_ocrin) in enumerate(zip(*infor)):
#                 # print(iret_box)
#                 count += 1
#                 cv2.rectangle(frame, (int(iret_box[0]), int(iret_box[1])), (int(iret_box[2]), int(iret_box[3])),
#                               (0, 255, 0), 2)
#                 font = cv2.FONT_HERSHEY_COMPLEX
#                 text = iret_ocrin
#                 frame = cv2ImgAddText(frame, text, int(iret_box[0]), int(iret_box[3]), (255, 0, 0), 25)
#             #cv2.imwrite(os.path.join(saved_path, "{}.jpg".format(str(count))), frame)
#         success, frame = videoCapture.read()
#     print(res)
#     print(fps)
#     print("识别率:","{:2.2f}".format((res/fps) * 100),"%")

if __name__ == '__main__':
    img_files = os.listdir(rootDir)
    count = 0
    num = 0
    cor = 0
    err = 0
    org = ""
    res = ""
   # print(img_files)
    img_list = None
    for filename in img_files:
        org = filename.split(".")[0]
        img_list = []
        img = cv2.imread(os.path.join(rootDir,filename))
        img_list.append(img)
        infor = HyperLPR_plate_recognition(img_list)
        if infor:
            num += 1
            for i, (iret_conf, iret_box, iret_ocrin) in enumerate(zip(*infor)):
                res = iret_ocrin.split("空")[0]
                count += 1
                cv2.rectangle(img, (int(iret_box[0]), int(iret_box[1])), (int(iret_box[2]), int(iret_box[3])), (0, 255, 0),
                              2)
                font = cv2.FONT_HERSHEY_COMPLEX
                text = iret_ocrin
                img = cv2ImgAddText(img, text, int(iret_box[0]), int(iret_box[3]), (255, 0, 0), 25)
            cv2.imwrite(os.path.join(saved_path, "{}.jpg".format(str(count))), img)
        if(org == res):
            cor += 1
    print("照片:",len(img_files))
    print("识别:",cor)
    print("准确率:","{:2.2f}".format((cor/len(img_files) * 100)),"%")
    print("识别率:","{:2.2f}".format((num/len(img_files) * 100)),"%")

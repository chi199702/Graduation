//
// Created by SWPUCWF 
//
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main(){
    cv::Mat img2_gauss,img2gray,bin2img,dst_x,abs_X,kernelX,img2thre,kernelY,dst,img;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> vec_4f;
//    读取图片
    cv::Mat image = cv::imread("/home/cwm/Graduation/photos/1.png");
    cv::GaussianBlur(image,img2_gauss,cv::Size(3,3),1);
    cv::cvtColor(img2_gauss,img2gray,cv::COLOR_RGB2GRAY);
//    # 求梯度算子
    cv::Sobel(img2gray,dst_x,CV_16S,1,0);
    cv::convertScaleAbs(dst_x,abs_X);
    img = abs_X;
//    # 图像二值化
    cv::threshold(img,img,0,255,cv::THRESH_OTSU);
//    # 闭操作,封闭轮廓
    kernelX = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(17,5));
    cv::morphologyEx(img,img,cv::MORPH_CLOSE,kernelX);

//  # 形态学处理
    kernelX = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(20,1));
    kernelY = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(1,19));
    cv::dilate(img,img,kernelX);
    cv::erode(img,img,kernelX);
    cv::erode(img,img,kernelY);
    cv::dilate(img,img,kernelY);
// # 平滑处理
    cv::GaussianBlur(img,img,cv::Size(15,1),1);
// # 查找轮廓
    cv::findContours(img,contours,vec_4f,cv::RETR_TREE,cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(image,contours,-1,cv::Scalar(0,0,255),2);
//    筛选
    {
        for (int i = 0; i < contours.size(); i++) {
            cout << contours.size() << endl;
            cv::Rect rect = cv::boundingRect(contours[i]);
            int x = rect.x;
            int y = rect.y;
            if (rect.width>(rect.height*2))
            {
//                cv::Mat chepai = image(cv::Rect(rect.x,rect.y,rect.width,rect.height));
//                cv::rectangle(chepai,cv::Point(rect.x,rect.y),cv::Point(rect.x + rect.width, rect.y + rect.height),cv::Scalar(0,255,0),2);
//                cv::imshow("car_num",chepai);
                cv::rectangle(image,cv::Point(rect.x,rect.y),cv::Point(rect.x + rect.width, rect.y + rect.height),cv::Scalar(0,255,0),2);

                //cv::waitKey(0);
            }
            cout << i << endl;
        }
    }

//    cv::imshow("test",image);
//    cv::waitKey(0);
    imwrite("/home/cwm/Graduation/photos/result.png", image);
    return 0;
}

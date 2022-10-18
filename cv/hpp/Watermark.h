/**
 * 通过叠加两张相同尺寸的图片来添加水印
 * */

#ifndef __WATERMARK__CPP
#define __WATERMARK__CPP

#include "BaseClass.h"

using namespace cv;
using namespace std;

class Watermark : public BaseClass {
public:
    Watermark() : BaseClass("Watermark") {}

    void InitParams(vector<void*> params) override;

    vector<vector<Mat>>& Execute() override;

    /**
     * @brief 将照片 dst 调整成和 src 相同的尺寸
     * */
    Mat ResizeToSrc(Mat& src, Mat& dst);

    /**
     * @brief 两张图片叠加
     * */
    Mat AddTwoMat(Mat& image1, Mat& image2);

private:
    string path;    // 水印照片的路径
};

REGISTER_CLASS(Watermark);

#endif
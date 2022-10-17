/**
 * 阈值处理
 * */

#ifndef __THRESHOLD__CPP
#define __THRESHOLD__CPP

#include "BaseClass.h"

using namespace cv;
using namespace std;

class Threshold : public BaseClass {
public:
    Threshold() : BaseClass("Threshold") {}

    void InitParams(vector<void*> params) override {
        // 按顺序给数据成员赋值
    }

    vector<vector<Mat>>& Execute() override {
        vector<vector<Mat>>& raw_images = get_raw_images();
        vector<Mat>& result_image = get_result_image();
        for (vector<Mat>& vec_images : raw_images) {
            for (Mat& image : vec_images) {
                result_image.push_back(_Threshold(image));
            }
        }

        PushBack(result_image);
        return get_result_image_s();
    }

    /**
     * @brief 阈值处理
     * */
    Mat _Threshold(Mat& image) {
        Mat result;
        threshold(image, result, 0, 255, THRESH_BINARY | THRESH_OTSU);
        
        return result;
    }
};

REGISTER_CLASS(Threshold);

#endif
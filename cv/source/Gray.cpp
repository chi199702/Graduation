/**
 * 灰度处理
 * */

#ifndef __GRAY__CPP
#define __GRAY__CPP

#include <initializer_list>
#include <vector>
#include "BaseClass.h"

using namespace cv;
using namespace std;

class Gray : public BaseClass {
public:
    Gray() : BaseClass("Gray") {}

    void InitParams(vector<void*> params) override {}

    vector<vector<Mat>>& Execute() override {
        vector<vector<Mat>>& raw_images = get_raw_images();
        vector<Mat>& result_image = get_result_image();
        for (vector<Mat>& vec_images : raw_images) {
            for (Mat& image : vec_images) {
                result_image.push_back(ToGray(image));
            }
        }
        PushBack(result_image);
        return get_result_image_s();
    }

    /**
     * @brief 灰度处理
     * */
    Mat& ToGray(Mat& image) {
        cvtColor(image, image, cv::COLOR_BGR2GRAY);
        return image;
    }

    
};

REGISTER_CLASS(Gray);

#endif


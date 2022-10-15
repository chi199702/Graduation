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

    void init_params(vector<void*> params) override {}

    vector<Mat>& execute() override {
        vector<vector<Mat>>& raw_images = get_raw_images();
        for (vector<Mat>& vec_images : raw_images) {
            for (Mat& image : vec_images) {
                images.push_back(ToGray(image));
            }
        }

        return images;
    }

    // 灰度处理
    Mat& ToGray(Mat& image) {
        cvtColor(image, image, cv::COLOR_BGR2GRAY);
        return image;
    }

private:
    vector<Mat> images;
};

#endif


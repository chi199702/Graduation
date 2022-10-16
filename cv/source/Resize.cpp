/**
 * 保持纵横比调整图片大小
 * */

#ifndef __RESIZE__CPP
#define __RESIZE__CPP

#include "BaseClass.h"

using namespace cv;
using namespace std;

class Resize : public BaseClass {
public:
    Resize() : BaseClass("Resize") {}

    void InitParams(vector<void*> params) override {
        unsigned int* _percent_of_scaling_pt = reinterpret_cast<unsigned int*>(params[0]);
        percent_of_scaling = *_percent_of_scaling_pt;
    }

    vector<vector<Mat>>& Execute() override {
        vector<vector<Mat>>& raw_images = get_raw_images();
        for (vector<Mat>& vec_images : raw_images) {
            for (Mat& image : vec_images) {
                images.push_back(Scale(image));
            }
        }
        PushBack(images);
        return get_result_image_s();
    }

    /**
     * 缩放
     * */
    Mat& Scale(Mat& image) {
        double new_width  = image.size().width  * percent_of_scaling / 100;
        double new_height = image.size().height * percent_of_scaling / 100;
        resize(image, image, Size(), new_width, new_height, INTER_AREA);

        return image;
    }

private:
    unsigned int percent_of_scaling;
    vector<Mat> images;
};

REGISTER_CLASS(Resize);

#endif
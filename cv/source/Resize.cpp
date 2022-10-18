#include "Resize.h"

void Resize::InitParams(vector<void*> params) {
    unsigned int* _percent_of_scaling_pt = reinterpret_cast<unsigned int*>(params[0]);
    percent_of_scaling = *_percent_of_scaling_pt;
}

vector<vector<Mat>>& Resize::Execute() {
    vector<vector<Mat>>& raw_images = get_raw_images();
    vector<Mat>& images = get_result_image();
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
Mat& Resize::Scale(Mat& image) {
    double new_width  = image.size().width  * percent_of_scaling / 100;
    double new_height = image.size().height * percent_of_scaling / 100;
    resize(image, image, Size(), new_width, new_height, INTER_AREA);

    return image;
}
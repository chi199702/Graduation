#include "Cut.h"

void Cut::InitParams(vector<void*> params) {
    unsigned int* _height_up_pt   = reinterpret_cast<unsigned int*>(params[0]);
    unsigned int* _height_down_pt = reinterpret_cast<unsigned int*>(params[1]);
    unsigned int* _width_left_pt  = reinterpret_cast<unsigned int*>(params[2]);
    unsigned int* _width_right_pt = reinterpret_cast<unsigned int*>(params[3]);

    height_up   = *_height_up_pt;
    height_down = *_height_down_pt;
    width_left  = *_width_left_pt;
    width_right = *_width_right_pt;
}

vector<vector<Mat>>& Cut::Execute() {
    vector<vector<Mat>>& raw_images = get_raw_images();
    vector<Mat>& result_image = get_result_image();
    for (vector<Mat>& vec_images : raw_images) {
        for (Mat& image : vec_images) {
            result_image.push_back(Trim(image));
        }
    }
    PushBack(result_image);
    return get_result_image_s();
}

Mat& Cut::Trim(Mat& image) {
    image = image(Range(height_up, height_down), Range(width_left, width_right));
    return image;
}
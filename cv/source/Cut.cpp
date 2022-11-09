#include "Cut.h"

void Cut::InitParams(vector<void*> params) {
    double* _height_up_pt   = reinterpret_cast<double*>(params[0]);
    double* _height_down_pt = reinterpret_cast<double*>(params[1]);
    double* _width_left_pt  = reinterpret_cast<double*>(params[2]);
    double* _width_right_pt = reinterpret_cast<double*>(params[3]);

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
    cout << "Cut 处理图片数量：" << result_image.size() << endl;
    PushBack(result_image);
    cout << "Cut::Execute() has execute success~" << endl; 
    return get_result_image_s();
}

Mat Cut::Trim(Mat& image) {
    const int MAX_WIDTH = image.size().width;
    const int MAX_HEIGHT = image.size().height;
    Mat result = image(Range(0, MAX_HEIGHT), Range(0, MAX_WIDTH));
    return result;
}
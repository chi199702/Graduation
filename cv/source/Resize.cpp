#include "Resize.h"

void Resize::InitParams(vector<void*> params) {
    double* _percent_of_scaling_pt = reinterpret_cast<double*>(params[0]);
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
    cout << "Resize 处理图片数量：" << images.size() << endl;
    PushBack(images);
    cout << "Resize::Execute() has execute success~" << endl;
    return get_result_image_s();
}

/**
 * 缩放
 * */
Mat Resize::Scale(Mat& image) {
    Mat dst;
    double new_width  = image.size().width  * (percent_of_scaling / 100);
    double new_height = image.size().height * (percent_of_scaling / 100);
    resize(image, dst, Size(new_width, new_height));
    return dst;
}
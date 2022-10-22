#include "Gray.h"

void Gray::InitParams(vector<void*> params) {}

vector<vector<Mat>>& Gray::Execute() {
    vector<vector<Mat>>& raw_images = get_raw_images();
    vector<Mat>& result_image = get_result_image();
    for (vector<Mat>& vec_images : raw_images) {
        for (Mat& image : vec_images) {
            result_image.push_back(ToGray(image));
        }
    }
    cout << "Gray 处理图片数量：" << result_image.size() << endl;
    PushBack(result_image);
    cout << "Gray::Execute() has execute success~" << endl;
    return get_result_image_s();
}

/**
 * @brief 灰度处理
 * */
Mat& Gray::ToGray(Mat& image) {
    cvtColor(image, image, cv::COLOR_BGR2GRAY);
    return image;
}
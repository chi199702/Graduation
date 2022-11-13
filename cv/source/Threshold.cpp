#include "Threshold.h"

void Threshold::InitParams(vector<void*> params) {}

vector<vector<Mat>>& Threshold::Execute() {
    cout << "Threshold~ start" << endl;
    vector<vector<Mat>>& raw_images = get_raw_images();
    vector<Mat>& result_image = get_result_image();
    for (vector<Mat>& vec_images : raw_images) {
        for (Mat& image : vec_images) {
            result_image.push_back(_Threshold(image));
        }
    }

    PushBack(result_image);
    cout << "Threshold~ end" << endl;
    return get_result_image_s();
}

Mat Threshold::_Threshold(Mat& image) {
    Mat result;
    threshold(image, result, 0, 255, THRESH_BINARY | THRESH_OTSU);
    
    return result;
}
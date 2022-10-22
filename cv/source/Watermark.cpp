#include "Watermark.h"

void Watermark::InitParams(vector<void*> params) {
    string* _path_pt = reinterpret_cast<string*>(params[0]);
    path = *_path_pt;
}

vector<vector<Mat>>& Watermark::Execute() {
    Mat logo = imread(path);

    vector<vector<Mat>>& raw_images = get_raw_images();
    vector<Mat>& result_image = get_result_image();
    for (vector<Mat>& v_images : raw_images) {
        for (Mat& image : v_images) {
            Mat _logo = logo;
            // 调整 _logo 的尺寸和当前要处理的图片尺寸一致
            Mat _logo_resize = ResizeToSrc(image, _logo);
            // 叠加两张图片
            Mat result = AddTwoMat(image, _logo_resize);
            result_image.push_back(result);
        }
    }
    cout << "Watermark 处理图片数量：" << result_image.size() << endl;
    PushBack(result_image);
    cout << "Watermark::Execute() has execute success~" << endl;
    return get_result_image_s();
}

/**
 * @brief 将照片 dst 调整成和 src 相同的尺寸
 * */
Mat Watermark::ResizeToSrc(Mat& src, Mat& dst) {
    Mat result;
    double new_width  = static_cast<double>(src.size().width);
    double new_height = static_cast<double>(src.size().height);
    resize(dst, result, Size(new_width, new_height));

    return result;
}

/**
 * @brief 两张图片叠加
 * */
Mat Watermark::AddTwoMat(Mat& image1, Mat& image2) {
    Mat result;
    if (image1.channels() == 1 || image2.channels() == 1) {
        if (image1.channels() != 1 && image2.channels() == 1) {
            cvtColor(image1, image1, cv::COLOR_BGR2GRAY);
        }else if (image1.channels() == 1 && image2.channels() != 1) {
            cvtColor(image2, image2, cv::COLOR_BGR2GRAY);
        }
    }
    addWeighted(image1, 0.9, image2, 0.1, 0, result);
    return result;
}
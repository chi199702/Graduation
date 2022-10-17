/**
 * 通过叠加两张相同尺寸的图片来添加水印
 * */

#ifndef __WATERMARK__CPP
#define __WATERMARK__CPP

#include "BaseClass.h"

using namespace cv;
using namespace std;

class Watermark : public BaseClass {
public:
    Watermark() : BaseClass("Watermark") {}

    void InitParams(vector<void*> params) override {
        string* _path_pt = reinterpret_cast<string*>(params[0]);
        path = *_path_pt;
    }

    vector<vector<Mat>>& Execute() override {
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

        PushBack(result_image);
        return get_result_image_s();
    }

    /**
     * @brief 将照片 dst 调整成和 src 相同的尺寸
     * */
    Mat ResizeToSrc(Mat& src, Mat& dst) {
        Mat result;
        resize(dst, result, src.size());

        return result;
    }

    /**
     * @brief 两张图片叠加
     * */
    Mat AddTwoMat(Mat& image1, Mat& image2) {
        Mat result;
        addWeighted(image1, 0.9, image2, 0.1, 0, result);

        return result;
    }

private:
    string path;    // 水印照片的路径
};

REGISTER_CLASS(Watermark);

#endif
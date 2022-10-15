#include <initializer_list>
#include <vector>
#include "Interface.h"

using cv::Mat;
using cv::cvtColor;
using std::initializer_list;
using std::vector;

class Gray : public Interface {
public:
    Gray() {}

    // 存放所有图片到 raw_image 里面
    Gray(initializer_list<vector<Mat>> v_images) {
        for (vector<Mat>& images : v_images) {      // 遍历每一张图片集
            for (Mat& image : images) {             // 遍历图片集中的每张图片
                raw_images.push_back(image);
            }
        }
    }

    vector<Mat>& execute() override {
        for (Mat& image : raw_images) {
            push_back(ToGray(image));
        }
    }

    // 灰度处理
    Mat& ToGray(Mat& image) {
        cvtColor(image, image, cv::COLOR_BGR2GRAY);
        return image;
    }

private:
    vector<Mat> raw_images;
};


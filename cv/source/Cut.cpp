#include <vector>
#include "Interface.h"

using cv::Mat;
using std::vector;

class Cut : public Interface {
public:
    Cut() {}

    Cut(unsigned int _width, unsigned int _height) : width(_width), height(_height) {}

    // 图片裁剪
    vector<Mat>& execute() override {

    }

    Mat& Trim(Mat& image) {
        
    }
private:
    unsigned int width;
    unsigned int height;
};
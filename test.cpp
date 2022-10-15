#include <gray.hpp>

using cv::Mat;
using cv::imread;
using cv::imwrite;

int main() {
    Mat src = imread("/data/cwm/Graduation/photos/1.png");
    Gray gray;
    src = gray.ToGray(src);
    imwrite("/data/cwm/Graduation/photos/result.png", src);
    return 0;
}
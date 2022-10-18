/**
 * 保持纵横比调整图片大小
 * */

#ifndef __RESIZE__CPP
#define __RESIZE__CPP

#include "BaseClass.h"

using namespace cv;
using namespace std;

class Resize : public BaseClass {
public:
    Resize() : BaseClass("Resize") {}

    void InitParams(vector<void*> params) override;

    vector<vector<Mat>>& Execute() override;

    /**
     * 缩放
     * */
    Mat& Scale(Mat& image);

private:
    unsigned int percent_of_scaling;
};

REGISTER_CLASS(Resize);

#endif
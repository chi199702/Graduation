/**
 * 指定范围裁剪图片
 * */

#ifndef __CUT__CPP
#define __CUT__CPP

#include <vector>
#include "BaseClass.h"

using namespace cv;
using namespace std;

class Cut : public BaseClass {
public:
    Cut() : BaseClass("Cut") {}

    void InitParams(vector<void*> params) override;

    vector<vector<Mat>>& Execute() override;

    Mat Trim(Mat& image);

private:
    unsigned int height_up;
    unsigned int height_down;
    unsigned int width_left;
    unsigned int width_right;
};

REGISTER_CLASS(Cut);

#endif
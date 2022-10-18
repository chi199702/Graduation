/**
 * 阈值处理
 * */

#ifndef __THRESHOLD__CPP
#define __THRESHOLD__CPP

#include "BaseClass.h"

using namespace cv;
using namespace std;

class Threshold : public BaseClass {
public:
    Threshold() : BaseClass("Threshold") {}

    void InitParams(vector<void*> params) override;

    vector<vector<Mat>>& Execute() override;

    /**
     * @brief 阈值处理
     * */
    Mat _Threshold(Mat& image);
};

REGISTER_CLASS(Threshold);

#endif
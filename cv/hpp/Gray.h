/**
 * 灰度处理
 * */

#ifndef __GRAY__CPP
#define __GRAY__CPP

#include <vector>
#include "BaseClass.h"

using namespace cv;
using namespace std;

class Gray : public BaseClass {
public:
    Gray() : BaseClass("Gray") {}

    void InitParams(vector<void*> params) override;

    vector<vector<Mat>>& Execute() override;

    /**
     * @brief 灰度处理
     * */
    Mat& ToGray(Mat& image);    
};

REGISTER_CLASS(Gray);

#endif


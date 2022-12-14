/**
 * 该类的功能
 * */

#ifndef __XXX__CPP
#define __XXX__CPP

#include "BaseClass.h"

using namespace cv;
using namespace std;

class class_name : public BaseClass {
public:
    class_name() : BaseClass("class_name") {}

    void InitParams(vector<void*> params) override {
        // 按顺序给数据成员赋值
    }

    vector<vector<Mat>>& Execute() override {
        vector<vector<Mat>>& raw_images = get_raw_images();
        vector<Mat>& result_image = get_result_image();
        for (vector<Mat>& vec_images : raw_images) {
            for (Mat& image : vec_images) {
                
            }
        }

        PushBack(result_image);
        return get_result_image_s();
    }

    /**
     * 在 Execute() 内部调用的其他函数
     * */

private:
    // 数据成员
};

REGISTER_CLASS(class_name);

#endif
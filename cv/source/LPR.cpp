/**
 * 车牌识别——调用 pythonmicroserver-update_weights/test.py
 * */

#ifndef __LPR__CPP
#define __LPR__CPP

#include "BaseClass.h"

using namespace cv;
using namespace std;

/**
 * 将父节点的结果全部写成图片，然后调用 test.py 进行车牌识别，再读入结果集图片为 Mat，再传给其他算子
 * */
class LPR : public BaseClass {
public:
    LPR() : BaseClass("LPR"), src_path("/home/cwm/Graduation/photos/"), dst_path("/home/cwm/Graduation/p_results/") {}

    void InitParams(vector<void*> params) override {}

    /**
     * 1、将 Mat 写出到 src_path
     * 2、开启一个子线程来执行 test.py
     * 3、将结果集读入成 Mat
     * */
    vector<vector<Mat>>& Execute() override {
        
    }

    /**
     * 将 Mat 写出到 src_path
     * */
    void WriteMat(vector<Mat>& images) {
        const int size = images.size();
        string prefix = src_path;
        
        for (int i = 0; i < size; ++i) {
            string name = to_string(i) + ".png";
            string complete_path = prefix + name;
            imwrite(complete_path, images[i]);
        }
    }

private:
    string src_path;
    string dst_path;
};

REGISTER_CLASS(LPR);

#endif
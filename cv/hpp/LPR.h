/**
 * 车牌识别——调用 pythonmicroserver-update_weights/test.py
 * */
#ifndef __LPR__CPP
#define __LPR__CPP

#include "BaseClass.h"
#include "ReaderImages.h"
#include "WriterImages.h"

using namespace cv;
using namespace std;

/**
 * 将父节点的结果全部写成图片，然后调用 test.py 进行车牌识别，再读入结果集图片为 Mat，再传给其他算子
 * */
class LPR : public BaseClass {
public:
    LPR() : BaseClass("LPR"), src_path("/home/cwm/Graduation/cv/photos_lpr"), dst_path("/home/cwm/Graduation/cv/photos_lpr_result") {}

    void InitParams(vector<void*> params) override;

    /**
     * @brief
     * 1、Mat 写出到 src_path 
     * 2、开启一个子线程来执行 test.py 
     * 3、将结果集读入成 Mat
     * */
    vector<vector<Mat>>& Execute() override;

    /**
     * @brief 将 Mat 写出到 src_path
     * @param images 图片集
     * */
    void WriteMat(vector<Mat>& images);

    /**
     * @brief 开启子线程来执行 shell 脚本
     * @param cmd 需要执行的脚本命令
     * */
    void ExecuteShell(string& cmd);

    /**
     * @brief 将结果图片读成 Mat
     * */
    vector<Mat> ReadImage();
private:
    string src_path;
    string dst_path;
};

REGISTER_CLASS(LPR);

#endif
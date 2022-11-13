/**
 * 读取图片
 * */
#ifndef __READER__CPP
#define __READER__CPP

#include <vector>
#include "BaseClass.h"
#include "ReaderImages.h"

using namespace cv;
using namespace std;

class Reader : public BaseClass {
public:
    Reader() : BaseClass("Reader"), path("/data/cwm/cv/phtots") {}

    void InitParams(vector<void*> params) override;

    /**
     * @brief 将 path 下的所有图片加入到 images 中
     * */
    vector<vector<Mat>>& Execute() override;

private:
    string path;
};

REGISTER_CLASS(Reader);

#endif
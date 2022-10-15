#ifndef __READER__CPP
#define __READER__CPP

#include <vector>
#include "BaseClass.h"

using namespace cv;
using namespace std;

class Reader : public BaseClass {
public:
    Reader() : BaseClass("Reader") {}

    void init_params(vector<void*> params) override {
        string* path_ptr = reinterpret_cast<string*>(params[0]);
        path = *path_ptr;
    }

    // 将 path 下的所有图片加入到 images 中
    vector<Mat>& execute() override {

    }

private:
    string path;
};

#endif
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
    Reader() : BaseClass("Reader"), path("/home/cwm/Graduation/photos") {}

    void InitParams(vector<void*> params) override {
        string* path_ptr_pt = reinterpret_cast<string*>(params[0]);
        path = *path_ptr_pt;
    }

    /**
     * @brief 将 path 下的所有图片加入到 images 中
     * */
    vector<vector<Mat>>& Execute() override {
        ReaderImages reader;
        vector<Mat>& images = get_result_image();
        images = reader.read(path);
        PushBack(images);

        return get_result_image_s();
    }

private:
    string path;
};

REGISTER_CLASS(Reader);

#endif
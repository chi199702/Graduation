#ifndef __WRITER__CPP
#define __WRITER__CPP

#include <string>
#include "BaseClass.h"
#include "WriterImages.h"

using namespace cv;
using namespace std;

class Writer : public BaseClass {
public:
    Writer() : BaseClass("Writer"), dst_path("/home/cwm/Graduation/p_results") {}

    void InitParams(vector<void*> params) override {
        string* dst_path_pt = reinterpret_cast<string*>(params[0]);
        dst_path = *dst_path_pt;
    }

    vector<vector<Mat>>& Execute() override {
        WriterImages writer;
        vector<vector<Mat>>& raw_images = get_raw_images();
        vector<Mat>& result_image = get_result_image();
        for (vector<Mat>& vec_images : raw_images) {
            writer.WriterMat(vec_images, dst_path);
        }

        PushBack(result_image);
        return get_result_image_s();
    }

private:
    string dst_path;
};

REGISTER_CLASS(Writer);

#endif
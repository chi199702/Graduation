#ifndef __CUT__CPP
#define __CUT__CPP

#include <vector>
#include "BaseClass.h"

using namespace cv;
using namespace std;

class Cut : public BaseClass {
public:
    Cut() : BaseClass("Cut") {}

    void init_params(vector<void*> params) override {
        unsigned int* _width_pt  = reinterpret_cast<unsigned int*>(params[0]);
        unsigned int* _height_pt = reinterpret_cast<unsigned int*>(params[1]);
        width = *_width_pt;
        height = *_height_pt;
    }

    vector<Mat>& execute() override {
        vector<vector<Mat>>& raw_images = get_raw_images();
        for (vector<Mat>& vec_images : raw_images) {
            for (Mat& image : vec_images) {
                images.push_back(Trim(image));
            }
        }
    }

    Mat& Trim(Mat& image) {
        
    }

private:
    unsigned int width;
    unsigned int height;
    vector<Mat> images;
};

#endif
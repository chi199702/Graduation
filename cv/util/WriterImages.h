#ifndef __WRITEIMAGES__H
#define __WRITEIMAGES__H

/**
 * 写 Mat 到指定的文件夹路径下
 * */
#include <opencv2/opencv.hpp>
#include <string>
#include "Uuid.h"

using namespace cv;
using namespace std;

class WriterImages {
public:
    WriterImages() {}

    void WriterMat(vector<Mat>& images, const string& path) {
        const int size = images.size();
        Uuid creator_name;
        string name = creator_name.create_uuid();
        for (int i = 0; i < size; ++i) {
            string file_path = path + "/" + name + ".jpg";
            imwrite(file_path, images[i]);
            name = creator_name.create_uuid();
        }
    }

};

#endif
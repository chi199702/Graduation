#ifndef __WRITEIMAGES__H
#define __WRITEIMAGES__H

/**
 * 写 Mat 到指定的文件夹路径下
 * */
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

class WriterImages {
public:
    WriterImages() {}

    void WriterMat(vector<Mat>& images, const string& path) {
        const uint size = images.size();
        for (int i = 0; i < size; ++i) {
            string file_path = path + "/" + to_string(i) + ".png";
            imwrite(file_path, images[i]);
        }
    }
};

#endif
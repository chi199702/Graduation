#ifndef __READIMAGES__H
#define __READIMAGES__H

/**
 * 读取文件夹内的所有图片
 * */
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;

class ReaderImages {
public:
    ReaderImages() {}

    vector<Mat> read(const string& dir_path) {
        String pattern = dir_path + "/*.png";
        vector<String> images_path;
        glob(pattern, images_path);

        vector<Mat> result;
        
        // 读取 PNG
        int size = images_path.size();
        for (int i = 0; i < size; ++i) {
            result.push_back(imread(images_path[i]));
        }

        pattern = dir_path + "/*.jpg";
        images_path.clear();
        glob(pattern, images_path);

        // 读取 JPG
        size = images_path.size();
        for (int i = 0; i < size; ++i) {
            result.push_back(imread(images_path[i]));
        }

        return result;
    }
};

#endif
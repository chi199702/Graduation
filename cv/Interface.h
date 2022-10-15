#ifndef __INTERFACE
#define __INTERFACE

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "ObjectFactory.h"

using cv::Mat;
using std::vector;
using std::string;

class Interface {
public:
    Interface(const string& _class_name = "Interface") : class_name(_class_name) {};
    
    void push_back(Mat& image) {
        images.push_back(image);
    }
    
    vector<Mat>& get_images() {
        return images;
    }

    string& get_class_name() {
        return class_name;
    }

    virtual vector<Mat>& execute() {}

    virtual ~Interface() {}

private:
    string class_name;
    vector<Mat> images;
};

#endif  // __INTERFACE
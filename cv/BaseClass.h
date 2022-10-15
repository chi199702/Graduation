#ifndef __INTERFACE
#define __INTERFACE

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include "ObjectFactory.h"

using namespace cv;
using namespace std;

class BaseClass {
public:
    BaseClass(const string& _class_name = "Interface") : class_name(_class_name) {};

    void PushBack(vector<Mat>& images) {
        result_images.push_back(images);
    }
    
    vector<vector<Mat>>& get_images() {
        return raw_images;
    }

    void set_raw_images(vector<vector<Mat>>& _raw_images) {
        raw_images = _raw_images;
    }

    vector<vector<Mat>>& get_raw_images() {
        return raw_images;
    }

    vector<vector<Mat>>& get_result_images() {
        return result_images;
    }

    string& get_class_name() {
        return class_name;
    }

    /**
     * 核心代码
     * 所有派生类必须在此函数中实现业务逻辑
     * */
    virtual vector<Mat>& execute() {}

    /**
     * 参数初始化
     * 所有的参数都存放在 params 中, 用户必须将参数手动从 void* 转型
     * */
    virtual void init_params(vector<void*> params) {}

    virtual ~BaseClass() {}

private:
    string class_name;
    vector<vector<Mat>> raw_images;
    vector<vector<Mat>> result_images;
};

#endif  // __INTERFACE
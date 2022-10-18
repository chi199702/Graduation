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

    /**
     * @brief 将结果推入 result_image_s
     * @param images 要存放的图片集
     * */
    void PushBack(vector<Mat>& images) {
        result_image_s.push_back(images);
    }
    
    void set_raw_images(vector<vector<Mat>>& _raw_images) {
        raw_images = _raw_images;
    }

    vector<vector<Mat>>& get_raw_images() {
        return raw_images;
    }

    vector<Mat>& get_result_image() {
        return result_image;
    }

    vector<vector<Mat>>& get_result_image_s() {
        return result_image_s;
    }

    string& get_class_name() {
        return class_name;
    }

    /**
     * @brief 核心代码，所有派生类必须在此函数中实现业务逻辑
     * */
    virtual vector<vector<Mat>>& Execute() {}

    /**
     * @brief 参数初始化，所有的参数都存放在 params 中, 用户必须将参数手动从 void* 转型
     * @param params 参数存放空间
     * */
    virtual void InitParams(vector<void*> params) {}

    virtual ~BaseClass() {}

private:
    string class_name;
    vector<Mat> result_image;
    vector<vector<Mat>> raw_images;
    vector<vector<Mat>> result_image_s;
};

#endif  // __INTERFACE
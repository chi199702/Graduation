#include "BaseClass.h"

BaseClass::BaseClass(const string& _class_name = "Interface") : class_name(_class_name) {};

void BaseClass::PushBack(vector<Mat>& images) {
    result_image_s.push_back(images);
}

void BaseClass::set_raw_images(vector<vector<Mat>>& _raw_images) {
    raw_images = _raw_images;
}

vector<vector<Mat>>& BaseClass::get_raw_images() {
    return raw_images;
}

vector<Mat>& BaseClass::get_result_image() {
    return result_image;
}

vector<vector<Mat>>& BaseClass::get_result_image_s() {
    return result_image_s;
}

string& BaseClass::get_class_name() {
    return class_name;
}

vector<vector<Mat>>& BaseClass::Execute() {}

void BaseClass::InitParams(vector<void*> params) {}

BaseClass::~BaseClass() {}
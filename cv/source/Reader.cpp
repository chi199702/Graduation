#include "Reader.h"

void Reader::InitParams(vector<void*> params) {
    string* path_ptr_pt = reinterpret_cast<string*>(params[0]);
    path = *path_ptr_pt;
}

/**
 * @brief 将 path 下的所有图片加入到 images 中
 * */
vector<vector<Mat>>& Reader::Execute() {
    ReaderImages reader;
    vector<Mat>& images = get_result_image();
    images = reader.read(path);
    cout << "Reader 读取图片数量：" << images.size() << endl;
    PushBack(images);
    cout << "Reader::Execute() has execute success~" << endl;
    return get_result_image_s();
}
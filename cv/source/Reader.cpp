#include "Reader.h"

void Reader::InitParams(vector<void*> params) {
    string* path_ptr_pt = reinterpret_cast<string*>(params[0]);
    path = *path_ptr_pt;
}

/**
 * @brief 将 path 下的所有图片加入到 images 中
 * */
vector<vector<Mat>>& Reader::Execute() {
    cout << "Reader~ start" << endl;
    ReaderImages reader;
    vector<Mat>& images = get_result_image();
    images = reader.read(path);
    PushBack(images);
    cout << "Reader~ end" << endl;
    return get_result_image_s();
}
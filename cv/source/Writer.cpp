#include "Writer.h"

void Writer::InitParams(vector<void*> params) {
    string* dst_path_pt = reinterpret_cast<string*>(params[0]);
    dst_path = *dst_path_pt;
}

vector<vector<Mat>>& Writer::Execute() {
    cout << "Writer~ start" << endl;
    WriterImages writer;
    vector<vector<Mat>>& raw_images = get_raw_images();
    vector<Mat>& result_image = get_result_image();
    for (vector<Mat>& vec_images : raw_images) {
        writer.WriterMat(vec_images, dst_path);
    }
    PushBack(result_image);
    cout << "Writer~ end" << endl;
    return get_result_image_s();
}
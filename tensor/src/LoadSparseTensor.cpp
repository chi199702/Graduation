#include "LoadSparseTensor.h"

void* LoadSparseTensor::Execute() {
    FILE* file = fopen(path.c_str(), "r");
    tnsLoadSparseTensor(&tensor, file, 1);

    set_done_sparse_tensor(&tensor);
    return &tensor;
}

void LoadSparseTensor::InitParams(vector<void*> params) {
    string* path_pt = reinterpret_cast<string*>(params[0]);
    path = *path_pt;
}

Type LoadSparseTensor::get_type() {
    return get_type();
}

LoadSparseTensor::~LoadSparseTensor() {}
#include "LoadDenseTensor.h"

void* LoadDenseTensor::Execute() {
    FILE* file = fopen(path.c_str(), "r");
    tnsLoadDenseTensor(&tensor, file);

    set_done_dense_tensor(&tensor);
    return &tensor;
}

void LoadDenseTensor::InitParams(vector<void*> params) {
    string* path_pt = reinterpret_cast<string*>(params[0]);
    path = *path_pt;
}

LoadDenseTensor::~LoadDenseTensor() {}
#include "LoadSparseTensor.h"

void* LoadSparseTensor::Execute() {
    cout << "LoadSparseTensor start~" << endl;
    FILE* file = fopen(path.c_str(), "r");
    tnsLoadSparseTensor(&tensor, file, 0);

    set_done_sparse_tensor(&tensor);
    cout << "LoadSparseTensor end~" << endl;
    return &tensor;
}

void LoadSparseTensor::InitParams(vector<void*> params) {
    string* path_pt = reinterpret_cast<string*>(params[0]);
    path = *path_pt;
}

LoadSparseTensor::~LoadSparseTensor() {}
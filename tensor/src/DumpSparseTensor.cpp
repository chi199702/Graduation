#include "DumpSparseTensor.h"

void* DumpSparseTensor::Execute() {
    FILE* file = fopen(path.c_str(), "w");
    vector<void*> raw_sprse_tensor = get_raw_sparse_tensor();
    tnsSparseTensor* tensor = reinterpret_cast<tnsSparseTensor*>(raw_sprse_tensor[0]);
    tnsDumpSparseTensor(tensor, file);

    set_done_sparse_tensor(&tensor);
    return &tensor;
}

void DumpSparseTensor::InitParams(vector<void*> params) {
    string* path_pt = reinterpret_cast<string*>(params[0]);
    path = *path_pt;
}

DumpSparseTensor::~DumpSparseTensor() {}
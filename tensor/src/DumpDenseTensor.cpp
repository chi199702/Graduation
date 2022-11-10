#include "DumpDenseTensor.h"

void* DumpDenseTensor::Execute() {
    FILE* file = fopen(path.c_str(), "w");
    vector<void*> raw_dense_tensor = get_raw_dense_tensor();
    tensor = reinterpret_cast<tnsDenseTensor*>(raw_dense_tensor[0]);
    tnsDumpDenseTensor(tensor, file);

    set_done_dense_matrix(&tensor);
    return tensor;
}

void DumpDenseTensor::InitParams(vector<void*> params) {
    string* path_pt = reinterpret_cast<string*>(params[0]);
    path = *path_pt;
}

DumpDenseTensor::~DumpDenseTensor() {}
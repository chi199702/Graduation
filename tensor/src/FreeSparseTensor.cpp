#include "FreeSparseTensor.h"

void* FreeSparseTensor::Execute() {
    vector<void*> sparse_tensor = get_raw_sparse_tensor();
    tnsSparseTensor* tensor = reinterpret_cast<tnsSparseTensor*>(sparse_tensor[0]);

    tnsFreeSparseTensor(tensor);
    return nullptr;
}

void FreeSparseTensor::InitParams(vector<void*> params) {}

Type FreeSparseTensor::get_type() {
    return get_type();
}

FreeSparseTensor::~FreeSparseTensor() {}
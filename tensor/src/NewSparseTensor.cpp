#include "NewSparseTensor.h"

void* NewSparseTensor::Execute() {
    vector<void*> raw_sparse_tensor = get_raw_sparse_tensor();
    tnsSparseTensor* tensor = reinterpret_cast<tnsSparseTensor*>(raw_sparse_tensor[0]);
    tnsNewSparseTensor(&result, tensor -> ndims, tensor -> nmodes, tensor -> nnz);

    set_done_sparse_tensor(&result);
    return &result;
}

void NewSparseTensor::InitParams(vector<void*> params) {}

NewSparseTensor::~NewSparseTensor() {}
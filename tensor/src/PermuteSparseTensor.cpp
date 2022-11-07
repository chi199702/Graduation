#include "PermuteSparseTensor.h"

void* PermuteSparseTensor::Execute() {
    vector<void*> raw_sprse_tensor = get_raw_sparse_tensor();
    tnsSparseTensor* tensor = reinterpret_cast<tnsSparseTensor*>(raw_sprse_tensor[0]);
    
    tnsSparseTensor tsr_2;
    tnsNewSparseTensor(&tsr_2, tensor -> ndims, tensor -> nmodes, tensor -> nnz);
    uint32_t order[3] = { 2, 0, 1 };
    tnsPermuteSpatsr(&tsr_2, tensor, order);

    set_done_sparse_tensor(&tsr_2);
    return &tsr_2;
}

void PermuteSparseTensor::InitParams(vector<void*> params) {}

PermuteSparseTensor::~PermuteSparseTensor() {}
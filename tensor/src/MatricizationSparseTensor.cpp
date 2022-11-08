#include "MatricizationSparseTensor.h"

void* MatricizationSparseTensor::Execute() {
    vector<void*>& raw_sparse_tensor = get_raw_sparse_tensor();
    tnsSparseTensor* tsr = reinterpret_cast<tnsSparseTensor*>(raw_sparse_tensor[0]);
    
    uint32_t row = 1;
    uint32_t col = 1;
    for(uint32_t i = 0; i < cutPoint; ++i)
        row *= tsr -> ndims[i];   ///< 矩阵化后的行大小
    for(uint32_t i = cutPoint; i < tsr -> nmodes; ++i)
        col *= tsr -> ndims[i];   ///< 矩阵化后的行大小

    
    tnsNewSparseMatrix(&spamtxa, row, col);
    tnsMatricizationSpatsr(&spamtxa, tsr, cutPoint);
    
    set_done_sparse_matrix(&spamtxa);
    return &spamtxa;
}

void MatricizationSparseTensor::InitParams(vector<void*> params) {
    uint32_t* cutPoint_pt = reinterpret_cast<uint32_t*>(params[0]);
    cutPoint = *cutPoint_pt;
}

Type MatricizationSparseTensor::get_type() {
    return get_type();
}

MatricizationSparseTensor::~MatricizationSparseTensor() {}
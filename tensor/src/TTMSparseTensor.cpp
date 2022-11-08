#include "TTMSparseTensor.h"

void* TTMSparseTensor::Execute() {
    uint32_t copt_mode = 0;
    vector<void*> raw_sparse_tensor = get_raw_sparse_tensor();
    vector<void*> raw_dense_matrix = get_raw_dense_matrix();
    tnsSparseTensor* tensorx = reinterpret_cast<tnsSparseTensor*>(raw_sparse_tensor[0]);
    tnsDenseMatrix* denmat = reinterpret_cast<tnsDenseMatrix*>(raw_dense_matrix[0]);

    
    tnsNewSparseTensor(&tensory, tensorx -> ndims, tensorx -> nmodes, tensorx -> nnz);
    tensory.ndims[copt_mode] = denmat -> ncols;
    tnsTTMSpatsr(&tensory, tensorx, denmat, copt_mode);
    
    set_done_sparse_tensor(&tensory);
    return &tensory;
}

void TTMSparseTensor::InitParams(vector<void*> params) {
    uint32_t* copt_mode_pt = reinterpret_cast<uint32_t*>(params[0]);
    copt_mode = *copt_mode_pt;
}

Type TTMSparseTensor::get_type() {
    return get_type();
}

TTMSparseTensor::~TTMSparseTensor() {}
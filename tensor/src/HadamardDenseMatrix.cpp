#include "HadamardDenseMatrix.h"

void* HadamardDenseMatrix::Execute() {
    vector<void*>& raw_dense_tensor = get_raw_dense_matrix();
    mtxa = reinterpret_cast<tnsDenseMatrix*>(raw_dense_tensor[0]);
    tnsDenseMatrix* mtxb = reinterpret_cast<tnsDenseMatrix*>(raw_dense_tensor[1]);
    tnsHadamardDenmat_rw(mtxa, mtxb);
    
    set_done_dense_matrix(mtxa);
    return mtxa;
}

void HadamardDenseMatrix::InitParams(vector<void*> params) {}

Type HadamardDenseMatrix::get_type() {
    return get_type();
}

HadamardDenseMatrix::~HadamardDenseMatrix() {}
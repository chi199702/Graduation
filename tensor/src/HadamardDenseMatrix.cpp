#include "HadamardDenseMatrix.h"

void* HadamardDenseMatrix::Execute() {
    vector<void*>& raw_dense_matrix = get_raw_dense_matrix();
    mtxa = reinterpret_cast<tnsDenseMatrix*>(raw_dense_matrix[0]);
    tnsDenseMatrix* mtxb = reinterpret_cast<tnsDenseMatrix*>(raw_dense_matrix[1]);
    tnsHadamardDenmat_rw(mtxa, mtxb);
    
    set_done_dense_matrix(mtxa);
    return mtxa;
}

void HadamardDenseMatrix::InitParams(vector<void*> params) {}

HadamardDenseMatrix::~HadamardDenseMatrix() {}
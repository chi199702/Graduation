#include "HadamardSparseMatrix.h"

void* HadamardSparseMatrix::Execute() {
    vector<void*>& raw_sparse_tensor = get_raw_sparse_matrix();
    tnsSparseMatrix* mtxa = reinterpret_cast<tnsSparseMatrix*>(raw_sparse_tensor[0]);
    tnsSparseMatrix* mtxb = reinterpret_cast<tnsSparseMatrix*>(raw_sparse_tensor[1]);

    tnsSparseMatrix result;
    tnsHadamardSpamat(&result, mtxa, mtxb);
    
    set_done_sparse_matrix(&result);
    return &result;
}

void HadamardSparseMatrix::InitParams(vector<void*> params) {}

HadamardSparseMatrix::~HadamardSparseMatrix() {}
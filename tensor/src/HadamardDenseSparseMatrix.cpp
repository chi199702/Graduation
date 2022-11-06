#include "HadamardDenseSparseMatrix.h"

void* HadamardDenseSparseMatrix::Execute() {
    vector<void*> raw_dense_matrix = get_raw_dense_matrix();
    vector<void*> raw_sparse_matrix = get_raw_dense_matrix();
    tnsDenseMatrix* mtxAA = reinterpret_cast<tnsDenseMatrix*>(raw_dense_matrix[0]);
    tnsSparseMatrix* mtxBB = reinterpret_cast<tnsSparseMatrix*>(raw_sparse_matrix[0]);

    tnsSparseMatrix mtxCC;
    tnsNewSparseMatrix(&mtxCC, mtxAA -> nrows, mtxAA -> ncols);

    set_done_sparse_matrix(&mtxCC);
    return &mtxCC;
}

void HadamardDenseSparseMatrix::InitParams(vector<void*> params) {}

HadamardDenseSparseMatrix::~HadamardDenseSparseMatrix() {}
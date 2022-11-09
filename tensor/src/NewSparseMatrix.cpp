#include "NewSparseMatrix.h"

void* NewSparseMatrix::Execute() {
    
    tnsNewSparseMatrix(&matrix, nrows, ncols);

    set_done_sparse_matrix(&matrix);
    return &matrix;
}

void NewSparseMatrix::InitParams(vector<void*> params) {
    double* nrows_pt = reinterpret_cast<double*>(params[0]);
    double* ncols_pt = reinterpret_cast<double*>(params[1]);
    nrows = *nrows_pt;
    ncols = *ncols_pt;
}

NewSparseMatrix::~NewSparseMatrix() {}
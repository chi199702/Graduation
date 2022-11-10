#include "NewDenseMatrix.h"

void* NewDenseMatrix::Execute() {
    tnsNewDenseMatrix(&matrix, nrows, ncols);
    set_done_dense_matrix(&matrix);
    return &matrix;
}

void NewDenseMatrix::InitParams(vector<void*> params) {
    double* nrows_pt = reinterpret_cast<double*>(params[0]);
    double* ncols_pt = reinterpret_cast<double*>(params[1]);
    nrows = *nrows_pt;
    ncols = *ncols_pt;
}

NewDenseMatrix::~NewDenseMatrix() {}
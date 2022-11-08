#include "NewSparseMatrix.h"

void* NewSparseMatrix::Execute() {
    
    tnsNewSparseMatrix(&matrix, nrows, ncols);

    set_done_sparse_matrix(&matrix);
    return &matrix;
}

void NewSparseMatrix::InitParams(vector<void*> params) {
    uint32_t* nrows_pt = reinterpret_cast<uint32_t*>(params[0]);
    uint32_t* ncols_pt = reinterpret_cast<uint32_t*>(params[1]);
    nrows = *nrows_pt;
    ncols = *ncols_pt;
}

Type NewSparseMatrix::get_type() {
    return get_type();
}

NewSparseMatrix::~NewSparseMatrix() {}
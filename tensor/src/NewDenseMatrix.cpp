#include "NewDenseMatrix.h"

void* NewDenseMatrix::Execute() {
    tnsDenseMatrix matrix;
    tnsNewDenseMatrix(&matrix, nrows, ncols);

    set_done_dense_matrix(&matrix);
    return &matrix;
}

void NewDenseMatrix::InitParams(vector<void*> params) {
    uint32_t* nrows_pt = reinterpret_cast<uint32_t*>(params[0]);
    uint32_t* ncols_pt = reinterpret_cast<uint32_t*>(params[1]);
    nrows = *nrows_pt;
    ncols = *ncols_pt;
}

Type NewDenseMatrix::get_type() {
    return get_type();
}

NewDenseMatrix::~NewDenseMatrix() {}
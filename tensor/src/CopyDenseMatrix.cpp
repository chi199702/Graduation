#include "CopyDenseMatrix.h"

void* CopyDenseMatrix::Execute() {
    vector<void*> raw_dense_matrix = get_raw_dense_matrix();
    tnsDenseMatrix* matrix = reinterpret_cast<tnsDenseMatrix*>(raw_dense_matrix[0]);

    tnsDenseMatrix mtx_B;
    tnsNewDenseMatrix(&mtx_B, matrix -> nrows, matrix -> ncols);
    tnsCopyDenseMatrix(&mtx_B, matrix);

    set_done_dense_matrix(&mtx_B);
    return &mtx_B;
}

void CopyDenseMatrix::InitParams(vector<void*> params) {}

Type CopyDenseMatrix::get_type() {
    return get_type();
}

CopyDenseMatrix::~CopyDenseMatrix() {}
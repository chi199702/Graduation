#include "KroneckerDenseMatrix.h"

void* KroneckerDenseMatrix::Execute() {
    vector<void*>& raw_dense_matrix = get_raw_dense_matrix();
    tnsDenseMatrix* martix1 = reinterpret_cast<tnsDenseMatrix*>(raw_dense_matrix[0]);
    tnsDenseMatrix* martix2 = reinterpret_cast<tnsDenseMatrix*>(raw_dense_matrix[1]);

    tnsNewDenseMatrix(&mtxc_dense, martix1 -> nrows * martix2 -> nrows, martix1 -> ncols * martix2 -> ncols);
    tnsKroneckerDenmtx(&mtxc_dense, martix1, martix2);

    set_done_dense_matrix(&mtxc_dense);
    return &mtxc_dense;
}

void KroneckerDenseMatrix::InitParams(vector<void*> params) {}

Type KroneckerDenseMatrix::get_type() {
    return get_type();
}

KroneckerDenseMatrix::~KroneckerDenseMatrix() {}
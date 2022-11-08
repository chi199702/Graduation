#include "ConstantDenseMatrix.h"

void* ConstantDenseMatrix::Execute() {
    tnsDenseMatrix matrix;
    tnsConstantDenseMatrix(&matrix, val);

    set_done_dense_matrix(&matrix);
    return &matrix;
}

void ConstantDenseMatrix::InitParams(vector<void*> params) {
    float* val_pt = reinterpret_cast<float*>(params[0]);
    val = *val_pt;
}

Type ConstantDenseMatrix::get_type() {
    return get_type();
}
ConstantDenseMatrix::~ConstantDenseMatrix() {}
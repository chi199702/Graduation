#include "ConstantDenseMatrix.h"

void* ConstantDenseMatrix::Execute() {
    cout << "ConstantDenseMatrix start ~" << endl;
    vector<void*> father_raw_dense_matrixs = get_raw_dense_matrix();
    tnsDenseMatrix* raw_dense_matrix = reinterpret_cast<tnsDenseMatrix*>(father_raw_dense_matrixs[0]);
    tnsConstantDenseMatrix(raw_dense_matrix, val);
    cout << val << endl;
    set_done_dense_matrix(raw_dense_matrix);
    cout << "ConstantDenseMatrix end ~" << endl;
    return raw_dense_matrix;
}

void ConstantDenseMatrix::InitParams(vector<void*> params) {
    double* val_pt = reinterpret_cast<double*>(params[0]);
    val = *val_pt;
}

ConstantDenseMatrix::~ConstantDenseMatrix() {}
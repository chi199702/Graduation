#include "FreeDenseMatrix.h"

void* FreeDenseMatrix::Execute() {
    vector<void*> dense_matrix = get_raw_dense_matrix();
    tnsDenseMatrix* matrix = reinterpret_cast<tnsDenseMatrix*>(dense_matrix[0]);

    tnsFreeDenseMatrix(matrix);
}

void FreeDenseMatrix::InitParams(vector<void*> params) {}

FreeDenseMatrix::~FreeDenseMatrix() {}
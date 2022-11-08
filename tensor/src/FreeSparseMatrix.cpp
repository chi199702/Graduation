#include "FreeSparseMatrix.h"

void* FreeSparseMatrix::Execute() {
    vector<void*> sparse_matrix = get_raw_sparse_matrix();
    tnsSparseMatrix* matrix = reinterpret_cast<tnsSparseMatrix*>(sparse_matrix[0]);

    tnsFreeSparseMatrix(matrix);
    return nullptr;
}

void FreeSparseMatrix::InitParams(vector<void*> params) {}

Type FreeSparseMatrix::get_type() {
    return get_type();
}

FreeSparseMatrix::~FreeSparseMatrix() {}
#include "FreeSparseMatrix.h"

void* FreeSparseMatrix::Execute() {
    vector<void*> sparse_matrix = get_raw_sparse_matrix();
    tnsSparseMatrix* matrix = reinterpret_cast<tnsSparseMatrix*>(sparse_matrix[0]);

    tnsFreeSparseMatrix(matrix);
}

void FreeSparseMatrix::InitParams(vector<void*> params) {}

FreeSparseMatrix::~FreeSparseMatrix() {}
#include "DumpSparseMatrix.h"

void* DumpSparseMatrix::Execute() {
    FILE* file = fopen(path.c_str(), "w");
    vector<void*> raw_sprse_matrix = get_raw_sparse_matrix();
    tnsSparseMatrix* matrix = reinterpret_cast<tnsSparseMatrix*>(raw_sprse_matrix[0]);
    tnsDumpSparseMatrix(matrix, file);

    set_done_sparse_matrix(&matrix);
    return &matrix;
}

void DumpSparseMatrix::InitParams(vector<void*> params) {
    string* path_pt = reinterpret_cast<string*>(params[0]);
    path = *path_pt;
}

Type DumpSparseMatrix::get_type() {
    return get_type();
}

DumpSparseMatrix::~DumpSparseMatrix() {}
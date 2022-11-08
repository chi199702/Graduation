#include "DumpDenseMatrix.h"

void* DumpDenseMatrix::Execute() {
    FILE* file = fopen(path.c_str(), "w");
    vector<void*> raw_dense_matrix = get_raw_dense_matrix();
    matrix = reinterpret_cast<tnsDenseMatrix*>(raw_dense_matrix[0]);
    tnsDumpDenseMatrix(matrix, file);

    set_done_dense_matrix(&matrix);
    return &matrix;
}

void DumpDenseMatrix::InitParams(vector<void*> params) {
    string* path_pt = reinterpret_cast<string*>(params[0]);
    path = *path_pt;
}

Type DumpDenseMatrix::get_type() {
    return get_type();
}

DumpDenseMatrix::~DumpDenseMatrix() {}
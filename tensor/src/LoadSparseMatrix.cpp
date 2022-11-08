#include "LoadSparseMatrix.h"

void* LoadSparseMatrix::Execute() {
    FILE* file = fopen(path.c_str(), "r");
    tnsLoadSparseMatrix(&martix, file);

    set_done_sparse_matrix(&martix);
    return &martix;
}

void LoadSparseMatrix::InitParams(vector<void*> params) {
    string* path_pt = reinterpret_cast<string*>(params[0]);
    path = *path_pt;
}

Type LoadSparseMatrix::get_type() {
    return get_type();
}

LoadSparseMatrix::~LoadSparseMatrix() {}
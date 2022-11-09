#include "LoadDenseMatrix.h"

void* LoadDenseMatrix::Execute() {
    FILE* file = fopen(path.c_str(), "r");
    tnsLoadDenseMatrix(&martix, file);

    set_done_dense_matrix(&martix);
    return &martix;
}

void LoadDenseMatrix::InitParams(vector<void*> params) {
    string* path_pt = reinterpret_cast<string*>(params[0]);
    path = *path_pt;
}

LoadDenseMatrix::~LoadDenseMatrix() {}
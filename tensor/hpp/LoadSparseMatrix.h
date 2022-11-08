#ifndef __LOADSPARSEMATRIX__H
#define __LOADSPARSEMATRIX__H

#include <vector>
#include <string>
#include <stdio.h>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 从文件读稀疏矩阵
 * */
class LoadSparseMatrix : public BaseClassTArm {
public:
    LoadSparseMatrix() : BaseClassTArm("LoadSparseMatrix", Type::SPARSEMATRIX) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    virtual Type get_type() override;
    ~LoadSparseMatrix();

private:
    string path;
    tnsSparseMatrix martix;
};

REGISTERTARM_CLASS(LoadSparseMatrix);
#endif
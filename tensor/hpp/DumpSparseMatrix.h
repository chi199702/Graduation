#ifndef __DUMPSPARSEMATRIX__H
#define __DUMPSPARSEMATRIX__H

#include <vector>
#include <stdio.h>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 打印稀疏矩阵
 * */
class DumpSparseMatrix : public BaseClassTArm {
public:
    DumpSparseMatrix() : BaseClassTArm("DumpSparseMatrix", Type::SPARSEMATRIX) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~DumpSparseMatrix();

private:
    string path;
    tnsSparseMatrix* matrix;
};

REGISTERTARM_CLASS(DumpSparseMatrix);
#endif
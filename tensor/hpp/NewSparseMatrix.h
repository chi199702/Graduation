#ifndef __NEWSPARSEMATRIX__H
#define __NEWSPARSEMATRIX__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 构造一个空的稀疏矩阵
 * */
class NewSparseMatrix : public BaseClassTArm {
public:
    NewSparseMatrix() : BaseClassTArm("NewSparseMatrix", Type::SPARSEMATRIX) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~NewSparseMatrix();

private:
    uint32_t nrows;
    uint32_t ncols;
    tnsSparseMatrix matrix;
};

REGISTERTARM_CLASS(NewSparseMatrix);
#endif
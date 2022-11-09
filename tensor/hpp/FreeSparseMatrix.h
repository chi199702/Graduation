#ifndef __FREESPARSEMATRIX__H
#define __FREESPARSEMATRIX__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * @brief 释放稀疏矩阵
 * */
class FreeSparseMatrix : public BaseClassTArm {
public:
    FreeSparseMatrix() : BaseClassTArm("FreeSparseMatrix", Type::NONE) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~FreeSparseMatrix();
};

REGISTERTARM_CLASS(FreeSparseMatrix);
#endif
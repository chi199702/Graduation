#ifndef __HADAMARDDENSESPARSEMATRIX__H
#define __HADAMARDDENSESPARSEMATRIX__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * @brief 稀疏矩阵和稠密矩阵的 Hadamard 积
 * */
class HadamardDenseSparseMatrix : public BaseClassTArm {
public:
    HadamardDenseSparseMatrix() : BaseClassTArm("HadamardDenseSparseMatrix", Type::SPARSEMATRIX) {};
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~HadamardDenseSparseMatrix();

private:
    tnsSparseMatrix mtxCC;
};

REGISTERTARM_CLASS(HadamardDenseSparseMatrix);
#endif
#ifndef __HADAMARDSPARSEMATRIX__H
#define __HADAMARDSPARSEMATRIX__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * @brief 另开空间的稀疏矩阵哈达玛积
 * */
class HadamardSparseMatrix : public BaseClassTArm {
public:
    HadamardSparseMatrix() : BaseClassTArm("HadamardSparseMatrix", Type::SPARSEMATRIX) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    virtual Type get_type() override;
    ~HadamardSparseMatrix();

private:
    tnsSparseMatrix result;
};

REGISTERTARM_CLASS(HadamardSparseMatrix);

#endif

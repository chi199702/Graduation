#ifndef __KRONECHERDENSEMATRIX__H
#define __KRONECHERDENSEMATRIX__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 稀疏矩阵 Kronecker 积
 * */
class KroneckerDenseMatrix : public BaseClassTArm {
public:
    KroneckerDenseMatrix() : BaseClassTArm("KroneckerDenseMatrix", Type::DENSEMATRIX) {};
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~KroneckerDenseMatrix();
};

REGISTERTARM_CLASS(KroneckerDenseMatrix);
#endif
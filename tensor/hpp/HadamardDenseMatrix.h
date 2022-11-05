#ifndef __HADAMARDDENSEMATRIX__H
#define __HADAMARDDENSEMATRIX__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

class HadamardDenseMatrix : public BaseClassTArm {
    HadamardDenseMatrix() : BaseClassTArm("HadamardDenseMatrix", Type::DENSEMATRIX) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~HadamardDenseMatrix();
};

#endif

#ifndef __CONSTANTDENSEMATRIX__H
#define __CONSTANTDENSEMATRIX__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 对稀疏张量进行转置和排序
 * */
class ConstantDenseMatrix : public BaseClassTArm {
public:
    ConstantDenseMatrix() : BaseClassTArm("ConstantDenseMatrix", Type::DENSETENSOR) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    virtual Type get_type() override;
    ~ConstantDenseMatrix();

private:
    float val;
    tnsDenseMatrix matrix;
};

REGISTERTARM_CLASS(ConstantDenseMatrix);
#endif
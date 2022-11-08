#ifndef __HADAMARDDENSEMATRIX__H
#define __HADAMARDDENSEMATRIX__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * @brief 覆盖原空间的稠密矩阵哈达玛积
 * */
class HadamardDenseMatrix : public BaseClassTArm {
public:
    HadamardDenseMatrix() : BaseClassTArm("HadamardDenseMatrix", Type::DENSEMATRIX) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    virtual Type get_type() override;
    ~HadamardDenseMatrix();

private:
    tnsDenseMatrix* mtxa;
};

REGISTERTARM_CLASS(HadamardDenseMatrix);

#endif

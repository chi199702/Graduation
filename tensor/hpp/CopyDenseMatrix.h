#ifndef __COPYDENSEMATRIX__H
#define __COPYDENSEMATRIX__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 拷贝一个稠密矩阵
 * */
class CopyDenseMatrix : public BaseClassTArm {
public:
    CopyDenseMatrix() : BaseClassTArm("CopyDenseMatrix", Type::DENSEMATRIX) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~CopyDenseMatrix();
};

REGISTERTARM_CLASS(CopyDenseMatrix);
#endif
#ifndef __FREEDENSESEMATRIX__H
#define __FREEDENSESEMATRIX__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 释放稠密矩阵
 * */
class FreeDenseMatrix : public BaseClassTArm {
public:
    FreeDenseMatrix() : BaseClassTArm("FreeDenseMatrix", Type::NONE) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    virtual Type get_type() override;
    ~FreeDenseMatrix();
};

REGISTERTARM_CLASS(FreeDenseMatrix);
#endif
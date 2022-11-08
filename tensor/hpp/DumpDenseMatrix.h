#ifndef __DUMPDENSEMATRIX__H
#define __DUMPDENSEMATRIX__H

#include <vector>
#include <stdio.h>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 打印稠密矩阵
 * */
class DumpDenseMatrix : public BaseClassTArm {
public:
    DumpDenseMatrix() : BaseClassTArm("DumpDenseMatrix", Type::DENSEMATRIX) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    virtual Type get_type() override;
    ~DumpDenseMatrix();

private:
    string path;
};

REGISTERTARM_CLASS(DumpDenseMatrix);
#endif
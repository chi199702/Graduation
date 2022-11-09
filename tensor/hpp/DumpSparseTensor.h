#ifndef __DUMPSPARSETENSOR__H
#define __DUMPSPARSETENSOR__H

#include <vector>
#include <stdio.h>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 打印稀疏矩阵
 * */
class DumpSparseTensor : public BaseClassTArm {
public:
    DumpSparseTensor() : BaseClassTArm("DumpSparseTensor", Type::SPARSETENSOR) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~DumpSparseTensor();

private:
    string path;
    tnsSparseTensor* tensor;
};

REGISTERTARM_CLASS(DumpSparseTensor);
#endif
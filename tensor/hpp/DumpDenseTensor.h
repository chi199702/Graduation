#ifndef __DUMPDENSETENSOR__H
#define __DUMPDENSETENSOR__H

#include <vector>
#include <stdio.h>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 打印稠密张量
 * */
class DumpDenseTensor : public BaseClassTArm {
public:
    DumpDenseTensor() : BaseClassTArm("DumpDenseTensor", Type::DENSETENSOR) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~DumpDenseTensor();

private:
    string path;
    tnsDenseTensor* tensor;
};

REGISTERTARM_CLASS(DumpDenseTensor);
#endif
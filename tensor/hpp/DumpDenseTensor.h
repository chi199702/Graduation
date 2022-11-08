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
    virtual Type get_type() override;
    ~DumpDenseTensor();

private:
    string path;
};

REGISTERTARM_CLASS(DumpDenseTensor);
#endif
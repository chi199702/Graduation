#ifndef __FREEDENSETENSOR__H
#define __FREEDENSETENSOR__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 释放稠密张量
 * */
class FreeDenseTensor : public BaseClassTArm {
public:
    FreeDenseTensor() : BaseClassTArm("FreeDenseTensor", Type::NONE) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~FreeDenseTensor();
};

REGISTERTARM_CLASS(FreeDenseTensor);
#endif
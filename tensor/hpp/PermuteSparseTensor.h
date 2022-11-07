#ifndef __PERMUTESPARSETENSOR__H
#define __PERMUTESPARSETENSOR__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 对稀疏张量进行转置和排序
 * */
class PermuteSparseTensor : public BaseClassTArm {
public:
    PermuteSparseTensor() : BaseClassTArm("PermuteSparseTensor", Type::SPARSETENSOR) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~PermuteSparseTensor();
};

REGISTERTARM_CLASS(PermuteSparseTensor);
#endif
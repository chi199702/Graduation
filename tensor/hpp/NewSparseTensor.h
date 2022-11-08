#ifndef __NEWSPARSETENSOR__H
#define __NEWSPARSETENSOR__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 构造一个空的稀疏张量
 * */
class NewSparseTensor : public BaseClassTArm {
public:
    NewSparseTensor() : BaseClassTArm("NewSparseTensor", Type::SPARSETENSOR) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    virtual Type get_type() override;
    ~NewSparseTensor();
};

REGISTERTARM_CLASS(NewSparseTensor);
#endif
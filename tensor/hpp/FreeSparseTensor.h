#ifndef __FREESPARSETENSOR__H
#define __FREESPARSETENSOR__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * @brief 释放稀疏张量
 * */
class FreeSparseTensor : public BaseClassTArm {
public:
    FreeSparseTensor() : BaseClassTArm("FreeSparseTensor", Type::NONE) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~FreeSparseTensor();
};

REGISTERTARM_CLASS(FreeSparseTensor);
#endif
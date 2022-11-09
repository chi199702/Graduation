#ifndef __TTMSPARSETENSOR__H
#define __TTMSPARSETENSOR__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * @brief 稀疏张量 * 矩阵，返回稀疏张量
 * */
class TTMSparseTensor : public BaseClassTArm {
public:
    TTMSparseTensor() : BaseClassTArm("TTMSparseTensor", Type::SPARSETENSOR) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~TTMSparseTensor();
private:
    uint32_t copt_mode;
    tnsSparseTensor tensory;
};

REGISTERTARM_CLASS(TTMSparseTensor);

#endif
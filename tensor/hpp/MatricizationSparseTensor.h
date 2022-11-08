#ifndef __MATRICIZATIONSPARSETENSOR__H
#define __MATRICIZATIONSPARSETENSOR__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * @brief 稀疏张量矩阵化
 * */
class MatricizationSparseTensor : public BaseClassTArm {
public:
    MatricizationSparseTensor() : BaseClassTArm("MatricizationSparseTensor", Type::SPARSEMATRIX) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    virtual Type get_type() override;
    ~MatricizationSparseTensor();
private:
    uint32_t cutPoint;
    tnsSparseMatrix spamtxa;
};

REGISTERTARM_CLASS(MatricizationSparseTensor);

#endif
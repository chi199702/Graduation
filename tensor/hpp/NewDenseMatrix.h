#ifndef __NewDenseMatrix__H
#define __NewDenseMatrix__H

#include <vector>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 构造一个空的稠密矩阵
 * */
class NewDenseMatrix : public BaseClassTArm {
public:
    NewDenseMatrix() : BaseClassTArm("NewDenseMatrix", Type::DENSEMATRIX) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    virtual Type get_type() override;
    ~NewDenseMatrix();

private:
    uint32_t nrows;
    uint32_t ncols;
    tnsDenseMatrix matrix;
};

REGISTERTARM_CLASS(NewDenseMatrix);
#endif
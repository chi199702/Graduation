#ifndef __LOADDENSEMATRIX__H
#define __LOADDENSEMATRIX__H

#include <vector>
#include <string>
#include <stdio.h>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 从文件读稠密矩阵
 * */
class LoadDenseMatrix : public BaseClassTArm {
public:
    LoadDenseMatrix() : BaseClassTArm("LoadDenseMatrix", Type::DENSEMATRIX) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    virtual Type get_type() override;
    ~LoadDenseMatrix();
    
private:
    string path;
    tnsDenseMatrix martix;
};

REGISTERTARM_CLASS(LoadDenseMatrix);
#endif
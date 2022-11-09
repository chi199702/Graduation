#ifndef __LOADSPARSETENSOR__H
#define __LOADSPARSETENSOR__H

#include <vector>
#include <string>
#include <stdio.h>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 从文件读稀疏张量
 * */
class LoadSparseTensor : public BaseClassTArm {
public:
    LoadSparseTensor() : BaseClassTArm("LoadSparseTensor", Type::SPARSETENSOR) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    ~LoadSparseTensor();

private:
    string path;
    tnsSparseTensor tensor;
};

REGISTERTARM_CLASS(LoadSparseTensor);
#endif
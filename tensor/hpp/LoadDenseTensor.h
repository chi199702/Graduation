#ifndef __LOADDENSETENSOR__H
#define __LOADDENSETENSOR__H

#include <vector>
#include <string>
#include <stdio.h>
#include "BaseClassTArm.h"

using namespace std;

/**
 * 从文件读稠密张量
 * */
class LoadDenseTensor : public BaseClassTArm {
public:
    LoadDenseTensor() : BaseClassTArm("LoadDenseTensor", Type::DENSETENSOR) {}
    virtual void* Execute() override;
    virtual void InitParams(vector<void*> params) override;
    virtual Type get_type() override;
    ~LoadDenseTensor();
    
private:
    string path;
    tnsDenseTensor tensor;
};

REGISTERTARM_CLASS(LoadDenseTensor);
#endif
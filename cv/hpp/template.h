#ifndef __CLASSNAME__H
#define __CLASSNAME__H

#include "BaseClass.h"

using namespace cv;
using namespace std;

class class_name : public BaseClass {
public:
    // 编辑构造函数
    class_name() : BaseClass("class_name") {}

    /**
     * @brief 参数初始化，所有的参数都存放在 params 中, 用户必须将参数手动从 void* 转型
     * @param params 参数存放空间
     * */
    void InitParams(vector<void*> params) override;

    /**
     * @brief 核心代码，所有派生类必须在此函数中实现业务逻辑
     * */
    vector<vector<Mat>>& Execute() override;

    /**
     * 在 Execute() 内部调用的其他函数
     * */

private:
    // 数据变量
};

REGISTER_CLASS(class_name);

#endif
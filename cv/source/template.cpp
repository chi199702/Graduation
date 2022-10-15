#include "BaseClass.h"

using namespace cv;
using namespace std;

class class_name : public BaseClass {
public:
    class_name() : BaseClass("class_name") {}

    void init_params(vector<void*> params) override {
        // 按顺序给数据成员赋值
    }

    vector<Mat>& execute() override {
        
    }

private:
    // 数据成员
};
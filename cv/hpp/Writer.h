#ifndef __WRITER__CPP
#define __WRITER__CPP

#include <string>
#include "BaseClass.h"
#include "WriterImages.h"

using namespace cv;
using namespace std;

class Writer : public BaseClass {
public:
    Writer() : BaseClass("Writer"), dst_path("/data/cwm/cv/results") {}

    void InitParams(vector<void*> params) override;

    vector<vector<Mat>>& Execute() override;

private:
    string dst_path;
};

REGISTER_CLASS(Writer);

#endif
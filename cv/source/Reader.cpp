#include <vector>
#include "Interface.h"

using cv::Mat;
using std::vector;
using std::string;

class Reader : public Interface {
public:
    Reader() :  {}

    Reader(const string& _path) : path(_path) {}

    // 将 path 下的所有图片加入到 images 中
    vector<Mat>& execute() override {

    }

private:
    string path;
};
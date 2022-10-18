/**
 * 处理器
 * */
#ifndef __PROCESS_H
#define __PROCESS_H

#include <opencv2/opencv.hpp>
#include <vector>
#include "json11.hpp"
#include "Header.h"

using namespace cv;
using namespace std;
using namespace json11;

class Processor {
public:
    Processor() {}

    Processor(const string& _str) : str(_str), json(Json::parse(str, json_error)) {}

    /**
     * @brief 处理核心
     * */
    void process();

    /**
     * @brief 根据类名返回实例
     * @param class_name 类名
     * */
    void* GetInstance(const string& class_name);

    
private:
    string str;
    string json_error;
    Json json;
};

#endif
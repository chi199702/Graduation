/**
 * 处理程序
 * */
#ifndef __PROCESS_H
#define __PROCESS_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <queue>
#include <unordered_map>
#include <set>
#include <memory>
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
     * @brief
     * 1. 维护父节点列表
     * 2. 维护参数列表
     * */
    void Init();

    /**
     * @brief 维护父节点列表和 [算子序号, 算子名称]
     * */
    void parse_father();

    /**
     * @brief 维护参数列表
     * */
    void parse_params();

    /**
     * @brief 处理核心
     * */
    void process();

    /**
     * @brief 执行一个算子
     * @param sequence 算子序号
     * */
    bool ExecuteModule(int sequence);

    /**
     * @brief 根据类名返回实例
     * @param class_name 类名
     * */
    void* GetInstance(const string& class_name);

    /**
     * @brief 判断改算子是否已经可以执行
     * @param sequence 算子序号
     * */
    bool JudgeExecution(int sequence);

    /**
     * @brief 释放参数列表 sequence_params
     * 由于 void* 指向的都是简单数据类型, 所以可以直接使用 delete void*
     * */
    ~Processor();
private:
    string str;                                         // 描述 DAG 图的 json
    string json_error;                                  // 描述解析出错的原因
    Json json;                                          // json 解析器
    set<int> visited;                                   // 已遍历过的算子
    priority_queue<int> pending;                        // 待执行队列
    unordered_map<int, string> sequence_name;           // [算子序号, 算子名称]
    unordered_map<int, vector<int>> sequence_father;    // 算子的父节点列表
    unordered_map<int, vector<void*>> sequence_params;  // 参数列表
    unordered_map<int, vector<vector<Mat>>> results;    // 执行结果
};

#endif
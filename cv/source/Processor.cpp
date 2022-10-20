#include "Processor.h"

void Processor::Init() {
    parse_father();
    parse_params();
}

void Processor::parse_father() {
    const int calculate_count = json.array_items().size();  // 算子总数
    for (int i = 0; i < calculate_count; ++i) {
        int sequence = json[i]["sequence"].int_value(); // 算子序号
        string name = json[i]["name"].string_value();   // 算子名称
        sequence_name[sequence] = name;

        vector<Json> fathers = json[i]["father"].array_items();
        for (Json father : fathers) {
            sequence_father[sequence].push_back(father.int_value());
        }
    }
}

void Processor::parse_params() {
    const int calculate_count = json.array_items().size();  // 算子总数
    for (int i = 0; i < calculate_count; ++i) {
        int sequence = json[i]["sequence"].int_value(); // 算子序号
        vector<Json> params = json[i]["parameter_list"].array_items();
        // 遍历参数列表
        for (Json param : params) {
            void* value;
            switch (param.type()) {
                case Json::Type::NUMBER:
                    value = new double(param.number_value());
                    break;
                case Json::Type::STRING:
                    value = new string(param.string_value());
                    break;
                case Json::Type::BOOL:
                    value = new bool(param.bool_value());
                    break;
            }
            sequence_params[sequence].push_back(value);
        }
    }
}

void Processor::process() {
    const int calculate_count = json.array_items().size();  // 算子总数
    int completed = 0;   // 已执行完成的算子个数

    while (completed < calculate_count) {
        // 遍历所有的算子，取出第一个未被遍历过的算子
        int no_visited = -1;
        for (int i = 0; i < calculate_count; ++i) {
            int sequence = json[i]["sequence"].int_value(); // 算子序号
            auto ite = visited.find(sequence);
            if (ite == visited.end()) {                     // 该算子未被遍历过
                no_visited = sequence;
                visited.insert(sequence);
                break;
            }
        }

        if (no_visited == -1) {     // 所有算子都已经遍历过了
            if (pending.empty()) {  // 所有算子都已经执行完毕
                break;
            }else {
                int sequence = pending.top();                    // 取出优先队列中的一个算子
                pending.pop();
                bool execute_result = ExecuteModule(sequence);   // 执行该算子
                if (!execute_result) {                           // 执行失败，存入优先队列
                    pending.push(sequence);
                }else {
                    ++completed;
                }
            }
        }else { // 执行该算子
            int sequence = no_visited;
            bool execute_result = ExecuteModule(sequence);   // 执行该算子
            if (!execute_result) {                           // 执行失败，存入优先队列
                pending.push(sequence);
            }else {
                ++completed;
            }
        }
    }
}

bool Processor::ExecuteModule(int sequence) {
    // 判断该算子是否可以执行
    if (!JudgeExecution(sequence)) {
        return false;
    }

    string& name = sequence_name[sequence];
    BaseClass* instance = reinterpret_cast<BaseClass*>(GetInstance(name));
    instance -> InitParams(sequence_params[sequence]);  // 为算子设置参数
    // 获取父节点的结果
    vector<vector<Mat>> fathers_result;
    vector<int> fathers = sequence_father[sequence];
    for (int father : fathers) {
        for (vector<Mat> images : results[father]) {
            fathers_result.push_back(images);
        }
    }
    instance -> set_raw_images(fathers_result); // 传递父节点的执行结果给算子
    // 执行算子
    vector<vector<Mat>>& result_image_s = instance -> Execute();
    // 存放算子执行结果
    results[sequence] = result_image_s;

    return true;
}

void* Processor::GetInstance(const string& class_name) {
    return ObjectFactory::CreateObject(class_name);
}

bool Processor::JudgeExecution(int sequence) {
    vector<int> fathers = sequence_father[sequence];
    if (fathers.empty()) {
        return true;
    }

    for (const int father : fathers) {
        if (visited.find(father) == visited.end()) {
            return false;
        }
    }

    return true;
}

Processor::~Processor() {
    for (pair<int, vector<void*>> p : sequence_params) {
        vector<void*> v_params = p.second;
        for (void* pt : v_params) {
            delete pt;
        }
    }
}
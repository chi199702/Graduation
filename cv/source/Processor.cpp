#include "Processor.h"

class Processor;

struct Package {
    Package(int _sequence, Processor* _process) : sequence(_sequence), process(_process) {}
    int sequence;
    Processor* process;
};

void* threadfunc(void* param);

Processor::Processor() {}

Processor::Processor(const string& _str, const bool _multi_thread) : str(_str), multi_thread(_multi_thread), json(Json::parse(str, json_error)) {}

void Processor::Init() {
    // 设置所有算子状态为 STATIC、将所有算子添加进待执行队列中
    const int calculate_count = json.array_items().size();
    for (int i = 0; i < calculate_count; ++i) {
        int sequence = json[i]["sequence"].int_value();
        sequence_state[sequence] = STATE::STATIC;
        pending.push(sequence);
    }
    parse_father();
    parse_params();
}

void Processor::parse_father() {
    const int calculate_count = json.array_items().size();
    for (int i = 0; i < calculate_count; ++i) {
        int sequence = json[i]["sequence"].int_value();
        string name = json[i]["name"].string_value();
        sequence_name[sequence] = name;

        vector<Json> fathers = json[i]["father"].array_items();
        for (Json father : fathers) {
            sequence_father[sequence].push_back(father.int_value());
        }
    }
}

void Processor::parse_params() {
    const int calculate_count = json.array_items().size();
    for (int i = 0; i < calculate_count; ++i) {
        int sequence = json[i]["sequence"].int_value();
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

void Processor::AgentExecute(int sequence) {
    // 判断该算子的父节点是否全部执行完毕
    if (!JudgeExecution(sequence)) {
        return;
    }
    if (multi_thread) {
        pthread_t thread;
        Package* package = new Package(sequence, this);
        if (pthread_create(&thread, NULL, threadfunc, package) != 0) {
            cout << "线程创建失败~" << endl;
            return;
        }
        // 当子线程先于父线程执行时,算子状态可能变为 STATE::END
        if (sequence_state[sequence] == STATE::STATIC) {
            sequence_state[sequence] = STATE::RUNNING;
        }
    }else {
        if (ExecuteModule(sequence)) {
            sequence_state[sequence] = STATE::END;
        }else {
            cout << "算子执行出错~" << endl;
        }
    }
}

void Processor::process() {
    Init();
    while (!pending.empty()) {
        int sequence = pending.front();
        pending.pop();
        AgentExecute(sequence);
        if (sequence_state[sequence] == STATE::STATIC) {
            pending.push(sequence);
        }
    }
    // 防止主线程先退出，子线程还没运行完成的情况
    int completed = 0;
    int calculate_count = json.array_items().size();
    while (completed < calculate_count) {
        completed = 0;
        for (auto p : sequence_state) {
            if (p.second == STATE::END) {
                ++completed;
            }
        }
    }
}

bool Processor::ExecuteModule(int sequence) {
    try {
        string& name = sequence_name[sequence];
        BaseClass* instance = reinterpret_cast<BaseClass*>(GetInstance(name));
        instance -> InitParams(sequence_params[sequence]);  // 为算子设置参数
        if (instance == nullptr) {
            throw runtime_error("exception occur in Processor.cpp::105, BaseClass* instance = reinterpret_cast<BaseClass*>(GetInstance(name))");
        }
        // 获取父节点的结果
        vector<vector<Mat>> fathers_result;
        vector<int> fathers = sequence_father[sequence];
        for (int father : fathers) {
            for (vector<Mat>& images : results[father]) {
                fathers_result.push_back(images);
            }
        }
        instance -> set_raw_images(fathers_result);
        // 执行算子
        vector<vector<Mat>>& result_image_s = instance -> Execute();
        // 存放算子执行结果
        results[sequence] = result_image_s;
    }catch (const runtime_error& error) {
        cout << error.what() << endl;
        exit(-1);
    }catch (const exception& error) {
        cout << error.what() << endl;
        exit(-1);
    }

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
        if (sequence_state[father] != STATE::END) {
            return false;
        }
    }

    return true;
}

void Processor::print() {
    for (auto p : sequence_name) {
        cout << p.first << " " << p.second << endl;
    }

    for (auto p : sequence_father) {
        cout << p.first << " ";
        cout << "[ ";
        for (int father : p.second) {
            cout << father << " ";
        }
        cout << " " << "]" << endl;
    }
}

void* threadfunc(void* param) {
    Package* package = reinterpret_cast<Package*>(param);
    int sequence = package -> sequence;
    Processor* process = package -> process;
    bool result = process -> ExecuteModule(sequence);
    bool* result_pt = new bool(result);
    // 设置该算子状态为已完成
    if (*result_pt) {
        process -> sequence_state[sequence] = Processor::STATE::END;
    }else {
        cout << "算子执行出错~" << endl;
    }
    return result_pt;
}

Processor::~Processor() {
    for (pair<int, vector<void*>> p : sequence_params) {
        vector<void*> v_params = p.second;
        for (void* pt : v_params) {
            delete pt;
        }
    }
}
#include "ProcessorTArm.h"

class ProcessorTArm;

struct Package {
    Package(int _sequence, ProcessorTArm* _process) : sequence(_sequence), process(_process) {}
    int sequence;
    ProcessorTArm* process;
};

void* threadfunc(void* param);

ProcessorTArm::ProcessorTArm() {}

ProcessorTArm::ProcessorTArm(const string& _str, const bool _multi_thread) : str(_str), multi_thread(_multi_thread), json(Json::parse(str, json_error)) {}

void ProcessorTArm::Init() {
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

void ProcessorTArm::parse_father() {
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

void ProcessorTArm::parse_params() {
    const int calculate_count = json.array_items().size();
    for (int i = 0; i < calculate_count; ++i) {
        int sequence = json[i]["sequence"].int_value();
        vector<Json> params = json[i]["parameter_list"].array_items();
        // 遍历参数列表
        for (Json param : params) {
            void* value;
            switch (param.type()) {
                case Json::Type::NUMBER: {
                    value = new double(param.number_value());
                    break;
                }
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

void ProcessorTArm::AgentExecute(int sequence) {
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

void ProcessorTArm::process() {
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

bool ProcessorTArm::ExecuteModule(int sequence) {
    try {
        string& name = sequence_name[sequence];
        BaseClassTArm* instance = reinterpret_cast<BaseClassTArm*>(GetInstance(name));
        instance -> InitParams(sequence_params[sequence]);
        sequence_type[sequence] = instance -> get_type();
        if (instance == nullptr) {
            throw runtime_error("exception occur in Processor.cpp::105, BaseClass* instance = reinterpret_cast<BaseClass*>(GetInstance(name))");
        }

        // 取出所有父节点的结果
        vector<int> fathers = sequence_father[sequence];
        vector<void*> father_raw_sparse_matrix;
        vector<void*> father_raw_dense_matrix;
        vector<void*> father_raw_sparse_tensor;
        vector<void*> father_raw_dense_tensor;
        for (int father : fathers) {
            Type father_type = sequence_type[father];
            void* void_result = results[father];
            // 判断父节点返回结果的类型，设置子节点对应的类型
            switch (father_type) {
                case Type::SPARSEMATRIX: {
                    tnsSparseMatrix* result1 = reinterpret_cast<tnsSparseMatrix*>(void_result);
                    father_raw_sparse_matrix.push_back(result1);
                    break;
                }
                case Type::DENSEMATRIX: {
                    tnsDenseMatrix* result2 = reinterpret_cast<tnsDenseMatrix*>(void_result);
                    father_raw_dense_matrix.push_back(result2);
                    break;
                }
                case Type::SPARSETENSOR: {
                    tnsSparseTensor* result3 = reinterpret_cast<tnsSparseTensor*>(void_result);
                    father_raw_sparse_tensor.push_back(result3);
                    break;
                }
                case Type::DENSETENSOR: {
                    tnsDenseTensor* result4 = reinterpret_cast<tnsDenseTensor*>(void_result);
                    father_raw_dense_tensor.push_back(result4);
                    break; 
                }
                case Type::NONE: {
                    break;
                }
            }
        }
        // 传递父节点结果到子节点中
        instance -> set_raw_sparse_matrix(father_raw_sparse_matrix);
        instance -> set_raw_dense_matrix(father_raw_dense_matrix);
        instance -> set_raw_sparse_tensor(father_raw_sparse_tensor);
        instance -> set_raw_dense_tensor(father_raw_dense_tensor);
        // 执行算子
        void* result = instance -> Execute();
        // 存放算子执行结果
        results[sequence] = result;
    }catch (const runtime_error& error) {
        cout << error.what() << endl;
        exit(-1);
        return false;
    }catch (const exception& error) {
        cout << error.what() << endl;
        exit(-1);
        return false;
    }

    return true;
}

void* ProcessorTArm::GetInstance(const string& class_name) {
    return ObjectFactoryTArm::CreateObject(class_name);
}

bool ProcessorTArm::JudgeExecution(int sequence) {
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

void ProcessorTArm::print() {
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
    ProcessorTArm* process = package -> process;
    bool result = process -> ExecuteModule(sequence);
    bool* result_pt = new bool(result);
    // 设置该算子状态为已完成
    if (*result_pt) {
        process -> sequence_state[sequence] = ProcessorTArm::STATE::END;
    }else {
        cout << "算子执行出错~" << endl;
    }
    return result_pt;
}

ProcessorTArm::~ProcessorTArm() {
    for (pair<int, vector<void*>> p : sequence_params) {
        vector<void*> v_params = p.second;
        for (void* pt : v_params) {
            delete pt;
        }
    }
}
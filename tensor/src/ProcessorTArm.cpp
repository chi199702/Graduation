#include "ProcessorTArm.h"

ProcessorTArm::ProcessorTArm() {}

ProcessorTArm::ProcessorTArm(const string& _str) : str(_str), json(Json::parse(str, json_error)) {}

void ProcessorTArm::Init() {
    parse_father();
    parse_params();
}

void ProcessorTArm::parse_father() {
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

void ProcessorTArm::parse_params() {
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

void ProcessorTArm::process() {
    Init();
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

bool ProcessorTArm::ExecuteModule(int sequence) {
    // 判断该算子是否可以执行
    if (!JudgeExecution(sequence)) {
        return false;
    }

    try {
        string& name = sequence_name[sequence];
        BaseClassTArm* instance = reinterpret_cast<BaseClassTArm*>(GetInstance(name));
        instance -> InitParams(sequence_params[sequence]);  // 为算子设置参数
        sequence_type[sequence] = instance -> get_type();   // 设置算子的返回类型
        if (instance == nullptr) {
            throw runtime_error("exception occur in Processor.cpp::105, BaseClass* instance = reinterpret_cast<BaseClass*>(GetInstance(name))");
        }

        // 获取父节点的结果
        vector<void*> fathers_result;
        vector<int> fathers = sequence_father[sequence];    // 父节点列表
        // 取出所有父节点的结果
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
                    break; }
                case Type::DENSEMATRIX: {
                    tnsDenseMatrix* result2 = reinterpret_cast<tnsDenseMatrix*>(void_result);
                    father_raw_dense_matrix.push_back(result2);
                    break; }
                case Type::SPARSETENSOR: {
                    tnsSparseTensor* result3 = reinterpret_cast<tnsSparseTensor*>(void_result);
                    father_raw_sparse_tensor.push_back(result3);
                    break; }
                case Type::DENSETENSOR: {
                    tnsDenseTensor* result4 = reinterpret_cast<tnsDenseTensor*>(void_result);
                    father_raw_dense_tensor.push_back(result4);
                    break; }
                case Type::NONE: {
                    break; }
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
    }catch (const exception& error) {
        cout << error.what() << endl;
        exit(-1);
    }
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
        if (visited.find(father) == visited.end()) {
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

ProcessorTArm::~ProcessorTArm() {
    for (pair<int, vector<void*>> p : sequence_params) {
        vector<void*> v_params = p.second;
        for (void* pt : v_params) {
            delete pt;
        }
    }
}
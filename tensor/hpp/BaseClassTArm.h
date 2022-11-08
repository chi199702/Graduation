#ifndef __BASECLASSTARM__H
#define __BASECLASSTARM__H

#include <string>
#include <vector>
#include <structs.h>
#include <TArm.h>
#include "ObjectFactoryTArm.h"

using namespace std;

enum Type {
    NONE, SPARSETENSOR, DENSETENSOR, SPARSEMATRIX, DENSEMATRIX, INDEXVECTOR, VALUEVECTOR
};

class BaseClassTArm {
public:
    BaseClassTArm(const string& _class_name = "Interface", const Type& _type = Type::SPARSETENSOR);

    /**
     * @brief 核心代码，所有派生类必须在此函数中实现业务逻辑
     * */
    virtual void* Execute();

    /**
     * @brief 参数初始化，所有的参数都存放在 params 中，用户必须将参数手动从 void* 转型
     * @param params 参数存放空间
     * */
    virtual void InitParams(vector<void*> params);

    virtual ~BaseClassTArm();

    // set and get
    void set_raw_sparse_tensor(vector<void*> spatsr);
    void set_raw_dense_tensor(vector<void*> dentsr);
    void set_raw_sparse_matrix(vector<void*> spamtx);
    void set_raw_dense_matrix(vector<void*> denmtx);
    void set_raw_index_vector(vector<void*> vec);
    void set_raw_value_vector(vector<void*> vec);

    vector<void*>& get_raw_sparse_tensor();
    vector<void*>& get_raw_dense_tensor();
    vector<void*>& get_raw_sparse_matrix();
    vector<void*>& get_raw_dense_matrix();
    vector<void*>& get_raw_index_vector();
    vector<void*>& get_raw_value_vector();

    void set_done_sparse_tensor(void*);
    void set_done_dense_tensor(void*);
    void set_done_sparse_matrix(void*);
    void set_done_dense_matrix(void*);
    void set_done_index_vector(void*);
    void set_done_value_vector(void*);

    void* get_done_sparse_tensor();
    void* get_done_dense_tensor();
    void* get_done_sparse_matrix();
    void* get_done_dense_matrix();
    void* get_done_index_vector();
    void* get_done_value_vector();

    virtual Type get_type();
private:
    string class_name;
    Type type;        // 结果的类型

    vector<void*> raw_sparse_tensor;
    vector<void*> raw_dense_tensor;
    vector<void*> raw_sparse_matrix;
    vector<void*> raw_dense_matrix;
    vector<void*> raw_index_vector;
    vector<void*> raw_value_vector;

    void* done_sparse_tensor;
    void* done_dense_tensor;
    void* done_sparse_matrix;
    void* done_dense_matrix;
    void* done_index_vector;
    void* done_value_vector;
};

#endif
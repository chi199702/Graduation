#include "BaseClassTArm.h"

BaseClassTArm::BaseClassTArm(const string& _class_name = "Interface", const Type& _type = Type::SPARSETENSOR) : class_name(_class_name), type(_type) {}

BaseClassTArm::~BaseClassTArm() {}

// set and get
void BaseClassTArm::set_raw_sparse_tensor(vector<void*> spatsr) {
    raw_sparse_tensor = spatsr;
}
void BaseClassTArm::set_raw_dense_tensor(vector<void*> dentsr) {
    raw_dense_tensor = dentsr;
}
void BaseClassTArm::set_raw_sparse_matrix(vector<void*> spamtx) {
    raw_sparse_matrix = spamtx;
}
void BaseClassTArm::set_raw_dense_matrix(vector<void*> denmtx) {
    raw_dense_matrix = denmtx;
}
void BaseClassTArm::set_raw_index_vector(vector<void*> vec) {
    raw_index_vector = vec;
}
void BaseClassTArm::set_raw_value_vector(vector<void*> vec) {
    raw_value_vector = vec;
}

vector<void*> BaseClassTArm::get_raw_sparse_tensor() {
    return raw_sparse_tensor;
}
vector<void*> BaseClassTArm::get_raw_dense_tensor() {
    return raw_dense_tensor;
}
vector<void*> BaseClassTArm::get_raw_sparse_matrix() {
    return raw_sparse_matrix;
}
vector<void*> BaseClassTArm::get_raw_dense_matrix() {
    return raw_dense_matrix;
}
vector<void*> BaseClassTArm::get_raw_index_vector() {
    return raw_index_vector;
}
vector<void*> BaseClassTArm::get_raw_value_vector() {
    return raw_value_vector;
}

void BaseClassTArm::set_done_sparse_tensor(void* _done_sparse_tensor) {
    done_sparse_tensor = _done_sparse_tensor;
}
void BaseClassTArm::set_done_dense_tensor(void* _done_dense_tensor) {
    done_dense_tensor = _done_dense_tensor;
}
void BaseClassTArm::set_done_sparse_matrix(void* _done_sparse_matrix) {
    done_sparse_matrix = _done_sparse_matrix;
}
void BaseClassTArm::set_done_dense_matrix(void* _done_dense_matrix) {
    done_dense_matrix = _done_dense_matrix;
}
void BaseClassTArm::set_done_index_vector(void* _done_index_vector) {
    done_index_vector = _done_index_vector;
}
void BaseClassTArm::set_done_value_vector(void* _done_value_vector) {
    done_value_vector = _done_value_vector;
}

void* BaseClassTArm::get_done_sparse_tensor() {
    return done_sparse_tensor;
}
void* BaseClassTArm::get_done_dense_tensor() {
    return done_dense_tensor;
}
void* BaseClassTArm::get_done_sparse_matrix() {
    return done_sparse_matrix;
}
void* BaseClassTArm::get_done_dense_matrix() {
    return done_dense_matrix;
}
void* BaseClassTArm::get_done_index_vector() {
    return done_index_vector;
}
void* BaseClassTArm::get_done_value_vector() {
    return done_value_vector;
}

Type BaseClassTArm::get_type() {
    return type;
}
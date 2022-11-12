#include "FreeSparseTensor.h"

void* FreeSparseTensor::Execute() {
    cout << "FreeSparseTensor start~" << endl;
    vector<void*> sparse_tensor = get_raw_sparse_tensor();
    tnsSparseTensor* tensor = reinterpret_cast<tnsSparseTensor*>(sparse_tensor[0]);
    tnsFreeSparseTensor(tensor);
    cout << "FreeSparseTensor end~" << endl;
    return nullptr;
}

void FreeSparseTensor::InitParams(vector<void*> params) {}

FreeSparseTensor::~FreeSparseTensor() {}
#include "FreeDenseTensor.h"

void* FreeDenseTensor::Execute() {
    vector<void*> dense_tensor = get_raw_dense_tensor();
    tnsDenseTensor* tensor = reinterpret_cast<tnsDenseTensor*>(dense_tensor[0]);

    tnsFreeDenseTensor(tensor);
    return nullptr;
}

void FreeDenseTensor::InitParams(vector<void*> params) {}

FreeDenseTensor::~FreeDenseTensor() {}
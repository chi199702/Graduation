#include "ObjectFactoryTArm.h"

void* ObjectFactoryTArm::CreateObject(const string& class_name) {
    const auto ite = dynamic_creator.find(class_name);
    if (ite == dynamic_creator.end()) {
        return nullptr;
    }else {
        NewInstancePt instance_pt = ite -> second;
        return instance_pt();
    }
}

void ObjectFactoryTArm::RegisterClass(const string& class_name, NewInstancePt func_pt) {
    dynamic_creator[class_name] = func_pt;
    cout << class_name << " has be registered~" << endl;
}

map<string, NewInstancePt> ObjectFactoryTArm::dynamic_creator;

RegisterTArm::RegisterTArm(const string& class_name, NewInstancePt func_pt) {
    ObjectFactoryTArm::RegisterClass(class_name, func_pt);
}
#include "ObjectFactory.h"

void* ObjectFactory::CreateObject(const string& class_name) {
    const auto ite = dynamic_creator.find(class_name);
    if (ite == dynamic_creator.end()) {
        return nullptr;
    }else {
        NewInstancePt instance_pt = ite -> second;
        return instance_pt();
    }
}

void ObjectFactory::RegisterClass(const string& class_name, NewInstancePt func_pt) {
    dynamic_creator[class_name] = func_pt;
    cout << class_name << " has be registered~" << endl;
}

map<string, NewInstancePt> ObjectFactory::dynamic_creator;

Register::Register(const string& class_name, NewInstancePt func_pt) {
    ObjectFactory::RegisterClass(class_name, func_pt);
}
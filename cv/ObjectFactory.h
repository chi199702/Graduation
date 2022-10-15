#ifndef __OBJECTFACTORY__H
#define __OBJECTFACTORY__H

#include <map>
#include <string>

using namespace std;

typedef void* (*NewInstancePt)();   // 函数指针

class ObjectFactory {
public:

    /**
     * 根据类名创建类实例
     * 1. 创建失败返回 Nullptr
     * 2. 创建成功返回 void*，返回后必须转为基类指针
     * */
    static void* CreateObject(const string& class_name) {
        auto ite = dynamic_creator.find(class_name);
        if (ite == dynamic_creator.end()) {
            return nullptr;
        }else {
            NewInstancePt instance_pt = ite -> second;
            return instance_pt();
        }
    }

    /**
     * 注册创造实例的函数指针到 dynamic_creator 中
     * */
    static void RegisterClass(const string& class_name, NewInstancePt instance_pt) {
        dynamic_creator[class_name] = instance_pt;
    }

private:
    static map<string, NewInstancePt> dynamic_creator;
};

map<string, NewInstancePt> ObjectFactory::dynamic_creator;

class Register {
    Register(const string& class_name, NewInstancePt instance_pt) {
        ObjectFactory::RegisterClass(class_name, instance_pt);
    }
};

/**
 * 每一个派生类都对应生成一个该注册类，用于将生成该派生类实例的函数指针注册到 dynamic_creator 中
 * */
#define REGISTER_CLASS(class_name)\
\
class class_name##Register {\
public:\
    static void* NewInstance() {\
        return new class_name();\
    }\
\
private:\
    static Register register;\
}\
\
Register class_name##Register::register(#class_name, class_name##Register::NewInstance);

#endif
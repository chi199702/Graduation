#ifndef __OBJECTFACTORYTARM__H
#define __OBJECTFACTORYTARM__H

#include <map>
#include <string>
#include <iostream>

using namespace std;

typedef void* (*NewInstancePt)();   // 函数指针

/**
 * 工厂类
 * 通过指定类名来获取实例
 * */
class ObjectFactoryTArm {
public:

    /**
     * @brief 根据类名创建类实例
     * 1. 创建失败返回 Nullptr
     * 2. 创建成功返回 void*，返回后必须转为基类指针
     * */
    static void* CreateObject(const string& class_name);

    /**
     * @brief 注册创造实例的函数指针到 dynamic_creator 中
     * @param class_name 类名
     * @param func_pt    能创造出实例的函数指针
     * */
    static void RegisterClass(const string& class_name, NewInstancePt func_pt);

private:
    static map<string, NewInstancePt> dynamic_creator;
};

/**
 * 用于向 dynamic_creator 中注册创建实例的函数指针
 * */
class RegisterTArm {
public:
    RegisterTArm(const string& class_name, NewInstancePt func_pt);
};

/**
 * 每一个派生类都对应生成一个该注册类，用于将生成该派生类实例的函数指针注册到 dynamic_creator 中
 * */
#define REGISTERTARM_CLASS(class_name)\
\
class class_name##RegisterTArm {\
public:\
    static void* NewInstance() {\
        return new class_name();\
    }\
\
private:\
    static RegisterTArm reg;\
};\
\
RegisterTArm class_name##RegisterTArm::reg(#class_name, class_name##RegisterTArm::NewInstance);

#endif
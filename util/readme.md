# 一、根据类名动态创建对象方式
## 1. 基类指针 —> 派生类对象

### 1) 初始化
    typedef void* (*NewInstancePt)();   // 函数指针
    map<string, NewInstancePt> creator; // 实例构造器
    
### 2) 创建对象
    使用宏定义为每一个派生类 class_name 创建一个实例构造器 class_name_creator，将该构造器注册到实例构造器 creator 中

# 二、如何接收不同类型的参数
## 1. 使用 void* 数组
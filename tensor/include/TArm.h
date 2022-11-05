#ifndef TARM_INCLUDED
#define TARM_INCLUDED

#include <stdio.h>
/*************************************************
 * TYPES
 *************************************************/
#ifdef TARM_INDEX_TYPEWIDTH
    #undef TARM_INDEX_TYPEWIDTH
    #define TARM_INDEX_TYPEWIDTH 32
#endif
#ifdef TARM_VALUE_TYPEWIDTH
    #undef TARM_VALUE_TYPEWIDTH
    #define TARM_VALUE_TYPEWIDTH 32
#endif

// 添加数据类型头文件
#include <TArm/types.h>

// 添加错误调试头文件
#include <TArm/error.h>

// 添加使用配置头文件
#include <TArm/macros.h>

// 添加主要结构体头文件
#include <TArm/structs.h>

// 添加 张量基础变换操作 的头文件
#include <TArm/vector.h>
#include <TArm/matrix.h>
#include <TArm/tensor.h>


// 添加执行计算的头文件
#include <TArm/compute.h>
#include <TArm/compute_rw.h>
#include <TArm/compute_t2m.h>

// 添加尝试新方法文件
// #include <TArm/tilespatsr.h>

#endif

#ifndef TARM_VECTOR_H
#define TARM_VECTOR_H

/*
索引向量部分
*/
/// 分配空间
int tnsNewIndexVector(tnsIndexVector *vec, tnsIndex const len);
void tnsFreeIndexVector(tnsIndexVector *vec);
/// 赋值&储存模块
/// 赋常数值 
int tnsConstantIndexVector(tnsIndexVector * const vec, tnsIndex const val);
/// 根据初始值赋连续数值
int tnsContinuousIndexVector(tnsIndexVector * const vec, tnsIndex val, tnsIndex step);
/// 拷贝Vector
int tnsCopyIndexVector(tnsIndexVector *dest, const tnsIndexVector *src);
int tnsPartCopyIndexVector(tnsIndexVector *dest, const tnsIndexVector *src, tnsIndex len);
/// 从文件读入
int tnsLoadIndexVector(tnsIndexVector *vec, FILE *fp);
/// 存入文件
int tnsDumpIndexVector(tnsIndexVector *vec, FILE *fp);
/// 添加元素
int tnsAppendIndexVector(tnsIndexVector *vec, tnsValue const val);


/// 操作模块
/// 交换索引和数值，返回到新数组中
int tnsMapSwapIndexVector(tnsIndexVector * dest, tnsIndexVector * src);

/*
ValueVector
*/
/// 分配空间
int tnsNewValueVector(tnsValueVector *vec, tnsIndex const len);
void tnsFreeValueVector(tnsValueVector *vec);
/// 赋值&储存模块
/// 赋常数值 
int tnsConstantValueVector(tnsValueVector * const vec, tnsValue const val);
/// 拷贝Vector
int tnsCopyValueVector(tnsValueVector *dest, const tnsValueVector *src);
/// 从文件读入
int tnsLoadValueVector(tnsValueVector *vec, FILE *fp);
/// 存入文件
int tnsDumpValueVector(tnsValueVector *vec, FILE *fp);
/// 添加元素
int tnsAppendValueVector(tnsValueVector *vec, tnsValue const val);

// Get属性模块（长度，范式，秩等等）





#endif
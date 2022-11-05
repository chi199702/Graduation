#ifndef TARM_COMPU_T2M_H
#define TARM_COMPU_T2M_H

/** 
*  @brief 该文件 包含各种 张量展开成矩阵计算 的相关函数声明。
*  特点是： 展开矩阵得到计算结果，再将结果存成张量等。
*  具有类似功能的函数写在附近。
*/

/** 
*  @brief 稀疏张量计算的函数
*/
// 稀疏张量矩阵化，将cutPoint前面的模态作为行，后面模态作为列。
int tnsMatricizationSpatsr(tnsSparseMatrix *mtx, const tnsSparseTensor *tsr, tnsIndex cutPoint);

// 并行稀疏张量矩阵化，将cutPoint前面的模态作为行，后面模态作为列。
int tnsOmpMatricizationSpatsr(tnsSparseMatrix *mtx, const tnsSparseTensor *tsr, tnsIndex cutPoint);

/**  
*  @brief 稠密张量计算的函数
*/


/**
*  @brief 稀疏矩阵计算的函数
*/


/**  
*  @brief 稠密矩阵计算的函数
*/






#endif
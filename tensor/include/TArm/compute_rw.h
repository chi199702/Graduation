#ifndef TARM_COMPU_RW_H
#define TARM_COMPU_RW_H

/** 
*  @brief 该文件 包含各种计算的相关函数声明。
*  特点是：（覆盖原空间存结果）
*  具有类似功能的函数写在附近。
*/

/** 
*  @brief 稀疏张量计算的函数
*/


/**  
*  @brief 稠密张量计算的函数
*/


/** 
*  @brief 稀疏矩阵计算的函数
*/



/** 
*  @brief 稠密矩阵计算的函数
*/

/// 稠密矩阵Hadamard积（覆盖原空间存结果）
int tnsHadamardDenmat_rw(tnsDenseMatrix *mtxa, const tnsDenseMatrix *mtxb);

/// 稠密矩阵Hadamard积（覆盖原空间存结果）
int tnsOmpHadamardDenmat_rw(tnsDenseMatrix *mtxa, const tnsDenseMatrix *mtxb);





#endif
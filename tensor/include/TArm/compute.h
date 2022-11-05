#ifndef TARM_COMPU_H
#define TARM_COMPU_H

/** 
*  @brief 该文件 包含各种计算的相关函数声明。
*  特点是：（新开辟空间存结果）
*  备注：具有类似功能的函数写在附近。
*/

/** 
*  @brief 稀疏张量计算的函数
*/
///  Sparse tensor times a vector (SpTTV)
int tnsTTVSpatsr(tnsSparseTensor *spatsrY, const tnsSparseTensor *spatsrX, const tnsValueVector *vec, tnsIndex copt_mode);
///  并行Sparse tensor times a vector (SpTTV)
int tnsOmpTTVSpatsr(tnsSparseTensor *spatsrY, const tnsSparseTensor *spatsrX, const tnsValueVector *vec, tnsIndex copt_mode);


/// SpTTM
int tnsTTMSpatsr(tnsSparseTensor *spatsrY, const tnsSparseTensor *spatsrX, const tnsDenseMatrix *denmat, tnsIndex copt_mode);
/// Parallel SpTTM
int tnsOMPTTMSpatsr(tnsSparseTensor *spatsrY, const tnsSparseTensor *spatsrX, const tnsDenseMatrix *denmat, tnsIndex copt_mode);


/// MTTKRP
int tnsOMPMTTKRPSpatsr(tnsSparseTensor *tsr, tnsDenseMatrix **U_list, tnsIndex const copt_mode, const tnsIndex tk);

/**  
*  @brief 稠密张量计算的函数
*/
///  稠密张量TTV
int tnsTTVDentsr(tnsDenseTensor *dentsrY, const tnsDenseTensor *dentsrX, const tnsValueVector *vec, tnsIndex copt_mode);

///  并行稠密张量TTV
int tnsOmpTTVDentsr(tnsDenseTensor *dentsrY, const tnsDenseTensor *dentsrX, const tnsValueVector *vec, tnsIndex copt_mode); 


/** 
*  @brief 稀疏矩阵计算的函数
*/

/// 稀疏矩阵Kronecker 积
int tnsKroneckerSpamtx(tnsSparseMatrix *mtxc, const tnsSparseMatrix *mtxa, tnsSparseMatrix *mtxb);
/// 并行稀疏矩阵Kronecker 积
int tnsOmpKhatriraoDenmtx(tnsDenseMatrix *mtxc, const tnsDenseMatrix *mtxa, const tnsDenseMatrix *mtxb, const tnsIndex tk);

/// 稀疏矩阵Hadamard积
int tnsHadamardSpamat(tnsSparseMatrix *mtxc, const tnsSparseMatrix *mtxa, const tnsSparseMatrix *mtxb);

///稀疏矩阵Hadamard积
int tnsOmpHadamardSpamat(tnsSparseMatrix *mtxc, const tnsSparseMatrix *mtxa, const tnsSparseMatrix *mtxb);

/// 稀疏矩阵和稠密矩阵Hadamard积
int tnsHadamardDenSpamat(tnsSparseMatrix *mtxc, const tnsDenseMatrix *mtxa, const tnsSparseMatrix *mtxb);

/// 并行稀疏矩阵和稠密矩阵Hadamard积
int tnsOmpHadamardDenSpamat(tnsSparseMatrix *mtxc, const tnsDenseMatrix *mtxa, const tnsSparseMatrix *mtxb);

/**  
*  @brief 稠密矩阵计算的函数
*/

/// 矩阵的转置乘以自身
// int tnsTransMulSelfDenmtx(tnsDenseMatrix *mtxb, const tnsDenseMatrix *mtxa);
int tnsDenseMatrixDotMulSeqTriangle(tnsIndex const mode, tnsIndex const nmodes, tnsDenseMatrix ** mats);
int tnsDenseMatrix2Norm(tnsDenseMatrix * const A, tnsValue * const lambda);
int tnsDenseMatrixMaxNorm(tnsDenseMatrix * const A, tnsValue * const lambda);
int tnsDenseMatrixSolveNormals(tnsIndex const mode, tnsIndex const nmodes, tnsDenseMatrix ** aTa, tnsDenseMatrix * rhs);

/// 稠密矩阵Kronecker 积
int tnsKroneckerDenmtx(tnsDenseMatrix *mtxc, const tnsDenseMatrix *mtxa, tnsDenseMatrix *mtxb);

/// 稠密矩阵Hadamard积
int tnsHadamardDenmat(tnsDenseMatrix *mtxc, const tnsDenseMatrix *mtxa, const tnsDenseMatrix *mtxb);

/// 并行稠密矩阵Hadamard积
int tnsOmpHadamardDenmat(tnsDenseMatrix *mtxc, const tnsDenseMatrix *mtxa, const tnsDenseMatrix *mtxb);

/// 稠密矩阵的Khatri-Rao乘积
int tnsKhatriraoDenmtx(tnsDenseMatrix *mtxc, const tnsDenseMatrix *mtxa, const tnsDenseMatrix *mtxb);







#endif
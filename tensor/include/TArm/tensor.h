#ifndef TARM_TENSOR_H
#define TARM_TENSOR_H


/*
稠密张量部分
*/
// 分配空间
int tnsNewDenseTensor(tnsDenseTensor *tsr, tnsIndex nmodes, const tnsIndex ndims[]);
// 释放空间
void tnsFreeDenseTensor(tnsDenseTensor *tsr);
// 构建常量张量
int tnsConstantDenseTensor(tnsDenseTensor * const tsr, tnsValue const val);
// 从文件读入稠密张量
int tnsLoadDenseTensor(tnsDenseTensor *tsr,FILE *fp);
// 将稠密张量写入文件
int tnsDumpDenseTensor(tnsDenseTensor *tsr,FILE *fp);


/*
稀疏张量部分
*/
// 分配空间
int tnsNewSparseTensor(tnsSparseTensor *tsr, const tnsIndex *ndims, tnsIndex nmodes, tnsIndex nnz);
void tnsFreeSparseTensor(tnsSparseTensor *tsr);

// 赋值&储存模块
// 赋常数值

// 拷贝Tensor
int tnsCopySparseTensor(tnsSparseTensor *dest, const tnsSparseTensor *src);
// 从文件读入稀疏张量, indextype表示0索引和1索引
int tnsLoadSparseTensor(tnsSparseTensor *tsr, FILE *fp, tnsIndex indextype);
// 存入文件稀疏张量
int tnsDumpSparseTensor(tnsSparseTensor *tsr, FILE *fp);

// 增加一个非零元
int tnsAddNNZSparseTensor(tnsSparseTensor *tsr, tnsIndexVector *nnz_inds, tnsValue nnz_val);

// Get属性模块（长度，范式，秩等等）



// 张量操作模块（包括矩阵乘加，矩阵转置等等）
// 稀疏张量多模态交换排序,注意这里B只是新开了自己ndim空间，inds和vals还是用的原来的空间
int tnsPermuteSpatsr(tnsSparseTensor *B, tnsSparseTensor *A, tnsIndex *order);

// 单模态内部重排序，也就是交换维度的顺序，使得密集的维度在一起，便于产生密集块。
void tnsLexiOrderPerMode(tnsSparseTensor * tsr, tnsIndex mode, tnsIndex ** orgIds, int tk);
void tnsBFSLike(tnsSparseTensor * tsr, tnsIndex ** newIndices);

void tnsSparseTensorSortIndexExceptSingleMode(tnsSparseTensor *tsr, int force, tnsIndex * mode_order, int const tk);
void tnsIndexRenumber(tnsSparseTensor * tsr, tnsIndex ** newIndices, int renumber, tnsIndex iterations, int tk);
void tnsSparseTensorShuffleIndices(tnsSparseTensor *tsr, tnsIndex ** map_inds);
#endif
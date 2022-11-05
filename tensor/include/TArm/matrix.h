#ifndef TARM_MATRIX_H
#define TARM_MATRIX_H

/*
稀疏矩阵部分
*/

// 分配空间
int tnsNewSparseMatrix(tnsSparseMatrix *mtx, tnsIndex const nrows, tnsIndex const ncols);
void tnsFreeSparseMatrix(tnsSparseMatrix *mtx);
// 从文件读入稀疏矩阵
int tnsLoadSparseMatrix(tnsSparseMatrix *mtx, FILE *fp);
int tnsDumpSparseMatrix(tnsSparseMatrix *mtx, FILE *fp);


/*
稠密矩阵部分
*/
// 分配空间
int tnsNewDenseMatrix(tnsDenseMatrix *mtx, tnsIndex const nrows, tnsIndex const ncols);
void tnsFreeDenseMatrix(tnsDenseMatrix *mtx);

// 赋值&储存模块
// 赋常数值
int tnsConstantDenseMatrix(tnsDenseMatrix * const mtx, tnsValue const val);
// 赋0-1的随机值
int tnsRandomDenseMatrix(tnsDenseMatrix * const mtx);
// 拷贝Matrxi
int tnsCopyDenseMatrix(tnsDenseMatrix *dest, const tnsDenseMatrix *src);
// 从张量转换成Matrix
int tnsSparseTensorToDenseMatrix(tnsDenseMatrix *dest, const tnsSparseTensor *src);
// 从稀疏Matrix转换成稠密Matrix
int tnsSparseMatrixToDenseMatrix(tnsDenseMatrix *dest, const tnsSparseTensor *src);
// 从文件读入稠密矩阵
int tnsLoadDenseMatrix(tnsDenseMatrix *mtx, FILE *fp);
// 存入文件稠密矩阵
int tnsDumpDenseMatrix(tnsDenseMatrix *mtx, FILE *fp);

// Get属性模块（长度，范式，秩等等）



// 矩阵操作模块（包括矩阵乘加，矩阵转置等等）




#endif
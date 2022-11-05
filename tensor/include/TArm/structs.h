#ifndef TARM_STRUCTS_H
#define TARM_STRUCTS_H


/**
 * Index Vector
 */
typedef struct {
    tnsIndex nlens;      /// # modes
    tnsIndex memory;      /// # malloc memory size
    tnsIndex *values;      /// non-zero values, length lens
} tnsIndexVector;

/**
 * Value Vector
 */
typedef struct {
    tnsIndex nlens;      /// # modes
    tnsIndex memory;      /// # malloc memory size
    tnsValue *values;      /// non-zero values, length nnz
} tnsValueVector;

/**
 * Sparse Tensors
 */
typedef struct {
    tnsIndex nmodes;      /// # modes
    tnsIndex *ndims;      /// size of each mode, length nmodes
    tnsIndex *sortorder;      /// size of each mode, length nmodes
    tnsIndex nnz;         /// 
    tnsIndexVector *inds;       /// indices of each element, length [nmodes][nnz]
    tnsValueVector values;      /// non-zero values, length nnz
} tnsSparseTensor;
/**
 * Dense Tensors
 */
typedef struct {
    tnsIndex nmodes;      /// # modes
    tnsIndex nnz;         /// nonzero size (multiply by all ndims)
    tnsIndex *ndims;      /// size of each mode, length nmodes
    tnsValueVector values;      /// non-zero values, length sum(ndims)
} tnsDenseTensor;



/**
 * Sparse Matrix(COO)
 */
typedef struct {
    tnsIndex nrows;      /// # modes
    tnsIndex ncols;      /// size of each mode, length nmodes
    //tnsIndex stride;    ///是大于ncols的最小8的倍数
    tnsIndex nnz;         /// 
    tnsIndexVector rowinds;       /// indices of each element, length rows
    tnsIndexVector colinds;       /// indices of each element, length cols
    tnsValueVector values;      /// non-zero values, length nnz
} tnsSparseMatrix;

/**
 * Dense Matrix
 */
typedef struct {
    tnsIndex nrows;      /// # modes
    tnsIndex ncols;      /// size of each mode, length nmodes
    tnsIndex stride;    ///是大于ncols的最小8的倍数
    tnsValueVector values;      /// non-zero values, length rows*cols
} tnsDenseMatrix;








#endif
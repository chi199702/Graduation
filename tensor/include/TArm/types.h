/*
    This file is part of TARM.

    TARM! is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.

    TARM! is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A TARMCULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with TARM!.
    If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TARM_TYPES_H
#define TARM_TYPES_H

#include <stdint.h>

/**
 * Define types, TODO: check the bit size of them, add branch for different settings
 */
#define TARM_ELEMENT_INDEX_TYPEWIDTH 8

#if TARM_INDEX_TYPEWIDTH == 32
  typedef uint32_t tnsIndex;
  typedef uint32_t tnsBlockIndex;
  #define TARM_INDEX_MAX UINT32_MAX
  #define TARM_PRI_INDEX PRIu32
  #define TARM_SCN_INDEX SCNu32
  #define TARM_PRI_BLOCK_INDEX PRIu32
  #define TARM_SCN_BLOCK_INDEX SCNu32
#elif TARM_INDEX_TYPEWIDTH == 64
  typedef uint64_t tnsIndex;
  typedef uint64_t tnsBlockIndex;
  #define TARM_INDEX_MAX UINT64_MAX
  #define TARM_PFI_INDEX PRIu64
  #define TARM_SCN_INDEX SCNu64
  #define TARM_PRI_BLOCK_INDEX PRIu64
  #define TARM_SCN_BLOCK_INDEX SCNu64
#else
  #error "Unrecognized TARM_INDEX_TYPEWIDTH."
#endif

#if TARM_VALUE_TYPEWIDTH == 32
  typedef float tnsValue;
  #define TARM_PRI_VALUE "f"
  #define TARM_SCN_VALUE "f"
#elif TARM_VALUE_TYPEWIDTH == 64
  typedef double tnsValue;
  #define TARM_PRI_VALUE "lf"
  #define TARM_SCN_VALUE "lf"
#else
  #error "Unrecognized TARM_VALUE_TYPEWIDTH."
#endif

#if TARM_ELEMENT_INDEX_TYPEWIDTH == 8
  typedef uint8_t tnsElementIndex;
  typedef uint16_t tnsBlockMatrixIndex;  // R < 256
  #define TARM_PRI_ELEMENT_INDEX PRIu8
  #define TARM_SCN_ELEMENT_INDEX SCNu8
  #define TARM_PRI_BLOCKMATRIX_INDEX PRIu16
  #define TARM_SCN_BLOCKMATRIX_INDEX SCNu16
#elif TARM_ELEMENT_INDEX_TYPEWIDTH == 16
  typedef uint16_t tnsElementIndex;
  typedef uint32_t tnsBlockMatrixIndex;
  #define TARM_PFI_ELEMENT_INDEX PRIu16
  #define TARM_SCN_ELEMENT_INDEX SCNu16
  #define TARM_PRI_BLOCKMATRIX_INDEX PRIu32
  #define TARM_SCN_BLOCKMATRIX_INDEX SCNu32
#elif TARM_ELEMENT_INDEX_TYPEWIDTH == 32
  typedef uint32_t tnsElementIndex;
  typedef uint32_t tnsBlockMatrixIndex;
  #define TARM_PFI_ELEMENT_INDEX PRIu32
  #define TARM_SCN_ELEMENT_INDEX SCNu32
  #define TARM_PRI_BLOCKMATRIX_INDEX PRIu32
  #define TARM_SCN_BLOCKMATRIX_INDEX SCNu32
#else
  #error "Unrecognized TARM_ELEMENT_INDEX_TYPEWIDTH."
#endif

typedef tnsBlockIndex tnsBlockNnzIndex;
#define TARM_PRI_BLOCKNNZ_INDEX TARM_PRI_BLOCK_INDEX
#define TARM_SCN_BLOCKNNZ_INDEX TARM_SCN_BLOCK_INDEX

typedef uint64_t tnsNnzIndex;
#define TARM_PRI_NNZ_INDEX PRIu64
#define TARM_SCN_NNZ_INDEX PRIu64

typedef unsigned __int128 tnsMortonIndex;
// typedef __uint128_t tnsMortonIndex;


#endif
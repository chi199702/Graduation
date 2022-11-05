
#ifndef TARM_MACROS_H
#define TARM_MACROS_H

/* User defined system configuration */
#define NUM_CORES 32    // for L size and determine privatilization or not
#define L1_SIZE 32000    // for B size
#define LLC_SIZE 40960000
#define PAR_DEGREE_REDUCE 20     // for determine privatilization or not  
#define PAR_MAX_DEGREE 100 // for L size
#define PAR_MIN_DEGREE 4 // for L size

#ifndef TARM_DEFAULT_NLOCKS
#define TARM_DEFAULT_NLOCKS 1024
#endif

#ifndef TARM_DEFAULT_LOCK_PAD_SIZE
#define TARM_DEFAULT_LOCK_PAD_SIZE 16
#endif

/**
 * An opaque data type to store a specific time point, using either CPU or GPU clock.
 */
typedef struct tnsTagTimer *tnsTimer;

typedef enum {
    TNSERR_NO_ERROR       = 0,
    TNSERR_UNKNOWN        = 1,
    TNSERR_SHAPE_MISMATCH = 2,
    TNSERR_VALUE_ERROR    = 3,
    TNSERR_ZERO_DIVISION  = 4,
    TNSERR_NO_MORE        = 99,
    TNSERR_OS_ERROR       = 0x10000,
    TNSERR_CUDA_ERROR     = 0x20000,
} TnsError;

#endif

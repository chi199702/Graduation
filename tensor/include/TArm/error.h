
#ifndef TARM_ERROR_H_INCLUDED
#define TARM_ERROR_H_INCLUDED

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// x为假的可能性更大
#ifndef unlikely
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif

/**
 * Check if a value is not zero, print error message and return.
 * @param errcode the value to be checked
 * @param module  the module name of current procedure
 * @param reason  human readable error explanation
 */
//  errcode 不为0，则报错，并终止程序 / 判断条件为真，则报错，并终止程序
// #ifndef NDEBUG
#define tns_CheckError(errcode, module, reason) \
    if(unlikely((errcode) != 0)) { \
        tns_ComplainError(module, (errcode), __FILE__, __LINE__, (reason)); \
        return (errcode); \
    }
// #else
// #define tns_CheckError(errcode, module, reason) 
//     if(unlikely((errcode) != 0)) { 
//         return (errcode); 
//     }
// #endif

// #ifndef NDEBUG
#define tns_CheckOmpError(errcode, module, reason) \
    if(unlikely((errcode) != 0)) { \
        tns_ComplainError(module, (errcode), __FILE__, __LINE__, (reason)); \
        exit(errcode); \
    }
// #else
// #define tns_CheckOmpError(errcode, module, reason) 
//     if(unlikely((errcode) != 0)) { 
//         exit(errcode); 
//     }
// #endif

/**
 * Check if a condition is true, set the error information as the system error, print error message and return.
 * @param cond   the condition to be checked
 * @param module the module name of current procedure
 */
//  cond 为1（也是不为0），则报错 / 判断条件为真，则报错，并终止程序。
//  cond 为1时，error置为0，终止,并输出报错结果。cond为NULL/0时，运行程序会继续运行。
#define tns_CheckOSError(cond, module) \
    if(unlikely((cond))) { \
        tns_CheckError(errno + TNSERR_OS_ERROR, (module), strerror(errno)); \
    }


void tns_ComplainError(const char *module, int errcode, const char *file, unsigned line, const char *reason);

#ifdef __cplusplus
}
#endif

#endif

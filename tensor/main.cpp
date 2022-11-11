#include <string>
#include <iostream>
#include "ProcessorTArm.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <getopt.h>
#include <TArm.h>

#ifdef __cplusplus
}
#endif

using namespace std;
using namespace json11;

int main() {
    /* string cwm_json = 
    R"(
      [
        {
          "name": "NewDenseMatrix",
          "parameter_list": [40000, 40000],
          "sequence": 1,
          "father": []
        },
        {
          "name": "NewDenseMatrix",
          "parameter_list": [40000, 40000],
          "sequence": 2,
          "father": []
        },
        {
          "name": "ConstantDenseMatrix",
          "parameter_list": [2.0],
          "sequence": 3,
          "father": [1]
        },
        {
          "name": "ConstantDenseMatrix",
          "parameter_list": [3.0],
          "sequence": 4,
          "father": [2]
        },
        {
          "name": "HadamardDenseMatrix",
          "parameter_list": [],
          "sequence": 5,
          "father": [3, 4]
        },
        {
          "name": "DumpDenseMatrix",
          "parameter_list": ["/data/cwm/pytools/re.tns"],
          "sequence": 6,
          "father": [5]
        },
        {
          "name": "FreeDenseMatrix",
          "parameter_list": [],
          "sequence": 7,
          "father": [6]
        }
      ]
    )";  */

    string cwm_json = 
    R"(
      [
        {
          "name": "LoadSparseTensor",
          "parameter_list": ["/data/cwm/spatns10000.tns"],
          "sequence": 1,
          "father": []
        },
        {
          "name": "LoadSparseTensor",
          "parameter_list": ["/data/cwm/spatns10000.tns"],
          "sequence": 2,
          "father": []
        },
        {
          "name": "PermuteSparseTensor",
          "parameter_list": [],
          "sequence": 3,
          "father": [1]
        },
        {
          "name": "PermuteSparseTensor",
          "parameter_list": [],
          "sequence": 4,
          "father": [2]
        },
        {
          "name": "DumpSparseTensor",
          "parameter_list": ["/data/cwm/res1.tns"],
          "sequence": 5,
          "father": [3]
        },
        {
          "name": "DumpSparseTensor",
          "parameter_list": ["/data/cwm/res2.tns"],
          "sequence": 6,
          "father": [4]
        },
        {
          "name": "FreeSparseTensor",
          "parameter_list": [],
          "sequence": 7,
          "father": [5, 6]
        }
      ]
    )"; 
    
    ProcessorTArm processor(cwm_json, true);
    processor.process();
    return 0;
}

        
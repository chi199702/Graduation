#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#include <getopt.h>
#include <TArm.h>

#ifdef __cplusplus
}
#endif

using namespace std;

int main() {
    string cwm_json = 
    R"(
      [
        {
          "name": "Reader",
          "parameter_list": ["/home/cwm/Graduation/cv/photos_raw"],
          "sequence": 1,
          "father": []
        },
        {
          "name": "Resize",
          "parameter_list": [80.0],
          "sequence": 2,
          "father": [1]
        },
        {
          "name": "Gray",
          "parameter_list": [],
          "sequence": 3,
          "father": [1]
        },
        {
          "name": "Cut",
          "parameter_list": [0, 200, 0, 200],
          "sequence": 4,
          "father": [1]
        },
        {
          "name": "Watermark",
          "parameter_list": ["/home/cwm/Graduation/watermark.jpg"],
          "sequence": 5,
          "father": [2, 3, 4]
        },
        {
          "name": "LPR",
          "parameter_list": [],
          "sequence": 6,
          "father": [5]
        },
        {
          "name": "Writer",
          "parameter_list": ["/home/cwm/Graduation/cv/photos_writer"],
          "sequence": 7,
          "father": [6]
        }
      ]
    )"; 

    return 0;
}

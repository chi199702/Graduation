#include <iostream>
#include "Processor.h"
#include <time.h>

using namespace cv;
using namespace std;
using namespace json11;

int main() {
    /* string cwm_json = 
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
          "father": [2]
        },
        {
          "name": "Cut",
          "parameter_list": [0, 200, 0, 200],
          "sequence": 4,
          "father": [2]
        },
        {
          "name": "Watermark",
          "parameter_list": ["/home/cwm/Graduation/watermark.jpg"],
          "sequence": 5,
          "father": [3, 4]
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
    )"; */

    /* string cwm_json = 
    R"(
      [
        {
          "name": "Reader",
          "parameter_list": ["/data/cwm/cv/phtots"],
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
          "parameter_list": [0, 50, 0, 50],
          "sequence": 4,
          "father": [1]
        },
        {
          "name": "Watermark",
          "parameter_list": ["/data/cwm/cv/watermark.jpg"],
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
          "parameter_list": ["/data/cwm/cv/results"],
          "sequence": 7,
          "father": [6]
        }
      ]
    )";  */

    string cwm_json = 
    R"(
      [
        {
          "name": "Reader",
          "parameter_list": ["/data/cwm/cv/phtots"],
          "sequence": 1,
          "father": []
        },
        {
          "name": "Reader",
          "parameter_list": ["/data/cwm/cv/phtots"],
          "sequence": 2,
          "father": []
        },
        {
          "name": "Reader",
          "parameter_list": ["/data/cwm/cv/phtots"],
          "sequence": 3,
          "father": []
        },
        {
          "name": "Cut",
          "parameter_list": [0, 50, 0, 50],
          "sequence": 4,
          "father": [1]
        },
        {
          "name": "Gray",
          "parameter_list": [],
          "sequence": 5,
          "father": [2]
        },
        {
          "name": "Resize",
          "parameter_list": [80.0],
          "sequence": 6,
          "father": [3]
        },
        {
          "name": "Watermark",
          "parameter_list": ["/data/cwm/cv/watermark.jpg"],
          "sequence": 7,
          "father": [4]
        },
        {
          "name": "Watermark",
          "parameter_list": ["/data/cwm/cv/watermark.jpg"],
          "sequence": 8,
          "father": [5]
        },
        {
          "name": "Watermark",
          "parameter_list": ["/data/cwm/cv/watermark.jpg"],
          "sequence": 9,
          "father": [6]
        },
        {
          "name": "LPR",
          "parameter_list": [],
          "sequence": 10,
          "father": [7]
        },
        {
          "name": "LPR",
          "parameter_list": [],
          "sequence": 11,
          "father": [8]
        },
        {
          "name": "LPR",
          "parameter_list": [],
          "sequence": 12,
          "father": [9]
        },
        {
          "name": "Writer",
          "parameter_list": ["/data/cwm/cv/results"],
          "sequence": 13,
          "father": [10, 11, 12]
        }
      ]
    )";
    time_t start = time(NULL);
    Processor process(cwm_json, true);
    process.process();
    time_t end = time(NULL);
    cout << "运行时间: " << difftime(end, start) << " s" << endl;
    return 0;
}
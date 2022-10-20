# Graduation
Chi Weiming's graduation project

string cwm_json = 
    R"(
      [
        {
          "name": "Reader",
          "parameter_list": ["/home/cwm/Graduation/cv/photos"],
          "sequence": 1,
          "father": []
        },
        {
          "name": "Resize",
          "parameter_list": [8],
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
          "parameter_list": ["/home/cwm/Graduation/cv/photo_results"],
          "sequence": 7,
          "father": [6]
        }
      ]
    )";

g++ /home/cwm/Graduation/cv/main.cpp /home/cwm/Graduation/cv/source/ObjectFactory.cpp /home/cwm/Graduation/cv/source/BaseClass.cpp /home/cwm/Graduation/cv/source/Cut.cpp /home/cwm/Graduation/cv/source/Gray.cpp /home/cwm/Graduation/cv/source/LPR.cpp /home/cwm/Graduation/cv/source/Processor.cpp /home/cwm/Graduation/cv/source/Reader.cpp /home/cwm/Graduation/cv/source/Threshold.cpp /home/cwm/Graduation/cv/source/Watermark.cpp /home/cwm/Graduation/cv/source/Writer.cpp /home/cwm/Graduation/cv/json11/json11.cpp -o cv_test -I/home/cwm/Graduation/cv/hpp -I/home/cwm/Graduation/cv/util -I/home/cwm/Graduation/cv/json11  `pkg-config --cflags --libs opencv`
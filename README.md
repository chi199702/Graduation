# Graduation
Chi Weiming's graduation project

g++ /home/cwm/Graduation/cv/main.cpp /home/cwm/Graduation/cv/source/ObjectFactory.cpp /home/cwm/Graduation/cv/source/BaseClass.cpp /home/cwm/Graduation/cv/source/Cut.cpp /home/cwm/Graduation/cv/source/Gray.cpp /home/cwm/Graduation/cv/source/LPR.cpp /home/cwm/Graduation/cv/source/Processor.cpp /home/cwm/Graduation/cv/source/Reader.cpp /home/cwm/Graduation/cv/source/Resize.cpp /home/cwm/Graduation/cv/source/Threshold.cpp /home/cwm/Graduation/cv/source/Watermark.cpp /home/cwm/Graduation/cv/source/Writer.cpp /home/cwm/Graduation/cv/json11/json11.cpp -g -o cv_test -I/home/cwm/Graduation/cv/hpp -I/home/cwm/Graduation/cv/util -I/home/cwm/Graduation/cv/json11  `pkg-config --cflags --libs opencv`

g++ Test.cpp -o test -I/home/cwm/armtensor/include -L/home/cwm/armtensor/build -lTArm -DTARM_INDEX_TYPEWIDTH=32 -DTARM_VALUE_TYPEWIDTH=32
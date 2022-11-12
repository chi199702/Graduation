# Graduation
Chi Weiming's graduation project

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

g++ /home/cwm/Graduation/cv/main.cpp /home/cwm/Graduation/cv/source/ObjectFactory.cpp /home/cwm/Graduation/cv/source/BaseClass.cpp /home/cwm/Graduation/cv/source/Cut.cpp /home/cwm/Graduation/cv/source/Gray.cpp /home/cwm/Graduation/cv/source/LPR.cpp /home/cwm/Graduation/cv/source/Processor.cpp /home/cwm/Graduation/cv/source/Reader.cpp /home/cwm/Graduation/cv/source/Resize.cpp /home/cwm/Graduation/cv/source/Threshold.cpp /home/cwm/Graduation/cv/source/Watermark.cpp /home/cwm/Graduation/cv/source/Writer.cpp /home/cwm/Graduation/cv/json11/json11.cpp -g -o cv_test -I/home/cwm/Graduation/cv/hpp -I/home/cwm/Graduation/cv/util -I/home/cwm/Graduation/cv/json11  `pkg-config --cflags --libs opencv`

g++ Test.cpp -o test -I/home/cwm/armtensor/include -L/home/cwm/armtensor/build -lTArm -DTARM_INDEX_TYPEWIDTH=32 -DTARM_VALUE_TYPEWIDTH=32

g++ \
/home/cwm/Graduation/tensor/main.cpp \
/home/cwm/Graduation/tensor/src/ObjectFactoryTArm.cpp \
/home/cwm/Graduation/tensor/src/BaseClassTArm.cpp \
/home/cwm/Graduation/tensor/src/ConstantDenseMatrix.cpp \
/home/cwm/Graduation/tensor/src/CopyDenseMatrix.cpp \
/home/cwm/Graduation/tensor/src/DumpDenseMatrix.cpp \
/home/cwm/Graduation/tensor/src/DumpDenseTensor.cpp \
/home/cwm/Graduation/tensor/src/DumpSparseMatrix.cpp \
/home/cwm/Graduation/tensor/src/DumpSparseTensor.cpp \
/home/cwm/Graduation/tensor/src/FreeDenseMatrix.cpp \
/home/cwm/Graduation/tensor/src/FreeDenseTensor.cpp \
/home/cwm/Graduation/tensor/src/FreeSparseMatrix.cpp \
/home/cwm/Graduation/tensor/src/FreeSparseTensor.cpp \
/home/cwm/Graduation/tensor/src/HadamardDenseMatrix.cpp \
/home/cwm/Graduation/tensor/src/HadamardDenseSparseMatrix.cpp \
/home/cwm/Graduation/tensor/src/HadamardSparseMatrix.cpp \
/home/cwm/Graduation/tensor/src/KroneckerDenseMatrix.cpp \
/home/cwm/Graduation/tensor/src/LoadDenseMatrix.cpp \
/home/cwm/Graduation/tensor/src/LoadDenseTensor.cpp \
/home/cwm/Graduation/tensor/src/LoadSparseMatrix.cpp \
/home/cwm/Graduation/tensor/src/LoadSparseTensor.cpp \
/home/cwm/Graduation/tensor/src/MatricizationSparseTensor.cpp \
/home/cwm/Graduation/tensor/src/NewDenseMatrix.cpp \
/home/cwm/Graduation/tensor/src/NewSparseMatrix.cpp \
/home/cwm/Graduation/tensor/src/NewSparseTensor.cpp \
/home/cwm/Graduation/tensor/src/PermuteSparseTensor.cpp \
/home/cwm/Graduation/tensor/src/ProcessorTArm.cpp \
/home/cwm/Graduation/tensor/src/TTMSparseTensor.cpp \
/home/cwm/Graduation/tensor/json11/json11.cpp \
-g -o tensor_test \
-I/home/cwm/Graduation/tensor/hpp \
-I/home/cwm/Graduation/tensor/json11 \
-I/home/cwm/Graduation/tensor/include \
-L/home/cwm/Graduation/tensor -lTArm -DTARM_INDEX_TYPEWIDTH=32 -DTARM_VALUE_TYPEWIDTH=32 \
-lpthread
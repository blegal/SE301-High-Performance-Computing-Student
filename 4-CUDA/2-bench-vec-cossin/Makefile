GCC       = g++
NVCC      = nvcc

# GCC
CFLAGS    = -I/usr/include/cuda -std=c++11 -Xcompiler "-Ofast -march=native -mtune=native -std=c++11 -fopenmp"
NVCCFLAGS = -I$(CUDAPATH)/include

# NVIDIA
CPPFLAGS  = -std=c++11 -Xcompiler "-Ofast -march=native -mtune=native -std=c++11 -fopenmp"

# LINKER
LDFLAGS   = -L/usr/lib64 -L$(CUDAPATH)/lib -lcuda -lm -Xcompiler -fopenmp -lgomp

CUDAPATH  = /usr/local/cuda
BUILD_DIR = build

EXEC = main

SRC=./src/cuda/kernel/vec_cossin.cu   \
    ./src/cuda/CUDACosSin.cu   \
    ./src/vcossin/vec_cossin_x86.cpp \
    ./src/main.cpp

# this is mac only. only linux system, remove -Xlinker and add in -lGL -lGLUT?

OBJ= $(SRC:.cu=.o)

all: $(EXEC)

main: $(OBJ)
	$(NVCC) $(CFLAGS) -o ./bin/$@ $^ $(LDFLAGS)

%.o: %.cu
	$(NVCC) $(NVCCFLAGS) $(CFLAGS) -o $@ -c $<

%.o: %.cpp
	$(GCC) $(CPPFLAGS) -o $@ -c $<

.PHONY: clean mrproper

clean:
	find ./bin -name $(EXEC) -exec rm {} \;
	find ./src -name *.o     -exec rm {} \;

mrproper: clean
	rm $(EXEC)

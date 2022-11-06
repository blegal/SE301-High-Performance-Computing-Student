NVCC      = nvcc
CFLAGS    = -Xcompiler "-fopenmp -Ofast -march=native -mtune=native -std=c++14"
NVCCFLAGS = -I$(CUDAPATH)/include
LDFLAGS   =-L$(CUDAPATH)/lib -lcuda -lcudart -lm -Xcompiler -fopenmp -lgomp

CUDAPATH = /usr/local/cuda
BUILD_DIR = build

EXEC = main

SRC=./src/cuda/kernel/vec_max_index.cu   \
    ./src/cuda/CUDAMaxIndex.cu   \
    ./src/vmax_index/vec_max_index_x86.cu \
    ./src/main.cu

# this is mac only. only linux system, remove -Xlinker and add in -lGL -lGLUT?

OBJ= $(SRC:.cu=.o)

all: $(EXEC)

main: $(OBJ)
	$(NVCC) $(CFLAGS) -o ./bin/$@ $^ $(LDFLAGS)

%.o: %.cu
	$(NVCC) $(NVCCFLAGS) $(CFLAGS) -o $@ -c $<

.PHONY: clean mrproper

clean:
	find ./bin -name $(EXEC) -exec rm {} \;
	find ./src -name *.o     -exec rm {} \;

mrproper: clean
	rm $(EXEC)

#pragma once
#include <cuda_runtime.h>
#include "helper/helper_cuda.h"

class CUDAMaxIndex
{
public:
    //
    // Buffers to hold data on host
    //

    //
    // Buffers to hold data on gpu device
    //

    int nElements;
    int nGroups;


public:

    CUDAMaxIndex(const int elements);

    void execute();

    int    N();

    void  load  (const float* src);
    int   result();
};

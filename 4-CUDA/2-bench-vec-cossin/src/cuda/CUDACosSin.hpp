#pragma once

class CUDACosSin
{
private:
    //
    // Buffers to hold data on host
    //
    float* host_A;
    float* host_B;
    float* host_C;

    //
    // Buffers to hold data on gpu device
    //
    float *gpu_A;
    float *gpu_B;
    float *gpu_C;

    int nElements;

    bool modified = false;

public:

    CUDACosSin(const int elements);

    void execute();

    float* ptr_C();
    int    N();

    void load_A (const float* src);
    void load_B (const float* src);
    void store_C(      float* dst);
};

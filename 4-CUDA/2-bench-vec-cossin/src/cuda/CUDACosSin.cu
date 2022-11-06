#include "CUDACosSin.hpp"
#include <iostream>

CUDACosSin::CUDACosSin(const int elements)
{
    nElements = elements;

    cudaError_t err = cudaSuccess;

    host_A = (float *)malloc( nElements * sizeof(float) );
    host_B = (float *)malloc( nElements * sizeof(float) );
    host_C = (float *)malloc( nElements * sizeof(float) );

    err = cudaMalloc((void **)&gpu_A, nElements * sizeof(float));
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to allocate device vector A (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaMalloc((void **)&gpu_B, nElements * sizeof(float));
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to allocate device vector B (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    err = cudaMalloc((void **)&gpu_C, nElements * sizeof(float));
    if (err != cudaSuccess) {
        fprintf(stderr, "Failed to allocate device vector C (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
}
/*
 *
 *
 *##############################################################################
 *
 *
 */
extern __global__ void cossin_arrays(const float *A, const float *B, float *C, int numElements);
/*
 *
 *
 *##############################################################################
 *
 *
 */
void CUDACosSin::execute()
{
    //
    // Launch the Vector Add CUDA Kernel
    //
    int threadsPerBlock = 256;
    int blocksPerGrid = (nElements + threadsPerBlock - 1) / threadsPerBlock;

    cossin_arrays<<<blocksPerGrid, threadsPerBlock>>>(gpu_A, gpu_B, gpu_C, nElements);

    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to launch vectorAdd kernel (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }

    modified = true;
}
/*
 *
 *
 *##############################################################################
 *
 *
 */
float* CUDACosSin::ptr_C()
{
    return host_C;
}
/*
 *
 *
 *##############################################################################
 *
 *
 */

int CUDACosSin::N()
{
    return nElements;
}
/*
 *
 *
 *##############################################################################
 *
 *
 */
void CUDACosSin::load_A(const float* src)
{
    int    length = N();
    for(int x = 0; x < length; x += 1)
        host_A[x] = src[x];

    cudaError_t err = cudaMemcpy(gpu_A, host_A, nElements * sizeof(float), cudaMemcpyHostToDevice);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy vector A from host to device (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
}
/*
 *
 *
 *##############################################################################
 *
 *
 */
void CUDACosSin::load_B(const float* src)
{
    int    length = N();
    for(int x = 0; x < length; x += 1)
        host_B[x] = src[x];

    cudaError_t err = cudaMemcpy(gpu_B, host_B, nElements * sizeof(float), cudaMemcpyHostToDevice);
    if (err != cudaSuccess)
    {
        fprintf(stderr, "Failed to copy vector A from host to device (error code %s)!\n", cudaGetErrorString(err));
        exit(EXIT_FAILURE);
    }
}
/*
 *
 *
 *##############################################################################
 *
 *
 */
void CUDACosSin::store_C(float* dst)
{
    if( modified == true )
    {
        cudaError_t err = cudaMemcpy(host_C, gpu_C, nElements * sizeof(float), cudaMemcpyDeviceToHost);
        if (err != cudaSuccess)
        {
            fprintf(stderr, "Failed to copy vector C from device to host (error code %s)!\n", cudaGetErrorString(err));
            exit(EXIT_FAILURE);
        }      
        modified = false;
    }

    float* ptr    = ptr_C();
    int    length = N();
    for(int x = 0; x < length; x += 1)
        dst[x] = ptr[x];
}
/*
 *
 *
 *##############################################################################
 *
 *
 */
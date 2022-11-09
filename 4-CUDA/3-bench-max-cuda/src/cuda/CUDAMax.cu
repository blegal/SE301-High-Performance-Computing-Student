/*
CPP translation of original Objective-C CUDAMax.m. Some stuff has been moved over to
the header. Source: https://developer.apple.com/documentation/metal/performing_calculations_on_a_gpu?language=objc

Original distribution license: LICENSE-original.txt.

Abstract:
A class to manage all of the Metal objects this app creates.
*/

#include "CUDAMax.hpp"
#include <iostream>
#include <cuda_runtime.h>
#include "helper/helper_cuda.h"

const int threadsPerBlock = 256;

CUDAMax::CUDAMax(const int elements)
{
    nElements = elements;
    
    nGroups   = (nElements + threadsPerBlock - 1) / threadsPerBlock;

}
/*
 *
 *
 *##############################################################################
 *
 *
 */
extern __global__ void reduce_max_float(const float *A, float *C, int numElements);
/*
 *
 *
 *##############################################################################
 *
 *
 */
void CUDAMax::execute()
{

}
/*
 *
 *
 *##############################################################################
 *
 *
 */
int CUDAMax::N()
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
void CUDAMax::load(const float* src)
{

}
/*
 *
 *
 *##############################################################################
 *
 *
 */
float CUDAMax::result()
{

}
/*
 *
 *
 *##############################################################################
 *
 *
 */

/*
CPP translation of original Objective-C CUDAMaxIndex.m. Some stuff has been moved over to
the header. Source: https://developer.apple.com/documentation/metal/performing_calculations_on_a_gpu?language=objc

Original distribution license: LICENSE-original.txt.

Abstract:
A class to manage all of the Metal objects this app creates.
*/

#include "CUDAMaxIndex.hpp"
#include <iostream>

const int threadsPerBlock = 256;

CUDAMaxIndex::CUDAMaxIndex(const int elements)
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
extern __global__ void reduce_max_index(
    const float*   array,
          float*   result_max,
          int32_t* result_idx,
    const int numElements);
;
/*
 *
 *
 *##############################################################################
 *
 *
 */
void CUDAMaxIndex::execute()
{

}
/*
 *
 *
 *##############################################################################
 *
 *
 */
int CUDAMaxIndex::N()
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
void CUDAMaxIndex::load(const float* src)
{

}
/*
 *
 *
 *##############################################################################
 *
 *
 */
int CUDAMaxIndex::result()
{

}
/*
 *
 *
 *##############################################################################
 *
 *
 */
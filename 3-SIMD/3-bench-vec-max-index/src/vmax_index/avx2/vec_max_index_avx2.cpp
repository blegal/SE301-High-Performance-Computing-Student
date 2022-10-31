/**
 *
 * 
  Copyright (c) 2012-2020 "Bordeaux INP, Bertrand LE GAL"
  bertrand.legal@ims-bordeaux.fr
  [http://legal.vvv.enseirb-matmeca.fr]

  This file is part of a LDPC library for realtime LDPC decoding
  on processor cores.
 *
 *
 */
#ifdef __AVX2__
#include "vec_max_index_avx2.hpp"
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <limits.h>
#include <immintrin.h>
/*
 *
 *
 *##############################################################################
 *
 *
 */
float vec_max_index_avx2(
        const float* __restrict src,
        const int               length)
{
    const int simd  = 8; // = sizeof(__m256) / sizeof(float);
    const int first = length & ~(simd - 1);

    const __m256i increment  = _mm256_setr_epi32(8, 8, 8, 8, 8, 8, 8, 8);
          __m256i indices    = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7);
          __m256i maxindices = indices;
          __m256  maxvalues  = _mm256_loadu_ps( src );

    for (int i = simd; i < first; i += simd)
    {
        indices = _mm256_add_epi32(indices, increment);
        const __m256 values = _mm256_loadu_ps (src + i);
        const __m256 gt     = _mm256_cmp_ps   (values, maxvalues, _CMP_GT_OQ);
        maxindices          = _mm256_blendv_epi8(maxindices, indices, _mm256_castps_si256(gt));
        maxvalues           = _mm256_max_ps   (values, maxvalues);
    }

    float   values_array [simd];
    int32_t indices_array[simd];

    _mm256_storeu_ps   (           values_array,  maxvalues);
    _mm256_storeu_si256( (__m256i*)indices_array, maxindices);

    int   maxindex = indices_array[0];
    float maxvalue =  values_array[0];
    
#if defined (__clang__)
    #pragma unroll
#endif
    for (int i = 1; i < simd; i++)
    {
        if (values_array[i] > maxvalue)
        {
            maxvalue = values_array [i];
            maxindex = indices_array[i];
        }
        else if( values_array[i] == maxvalue )
        {
            if( maxindex > indices_array[i] )
            {
                maxvalue = values_array [i];
                maxindex = indices_array[i];
            }
        }
    }

    return maxindex;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
#endif
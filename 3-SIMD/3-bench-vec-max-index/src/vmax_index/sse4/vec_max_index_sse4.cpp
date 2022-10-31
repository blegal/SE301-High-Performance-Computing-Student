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
#ifdef __SSE4_2__
#include "vec_max_index_sse4.hpp"
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
int vec_max_index_sse4(
        const float* __restrict src,
        const int               length)
{
    const int simd  = sizeof(__m128) / sizeof(float);
    const int first = length & ~(simd - 1);

    const __m128i increment  = _mm_setr_epi32(4, 4, 4, 4);
          __m128i indices    = _mm_setr_epi32(0, 1, 2, 3);
          __m128i maxindices = indices;
          __m128  maxvalues  = _mm_loadu_ps( src );

    for (int i = simd; i < first; i += simd) {

        indices = _mm_add_epi32(indices, increment);
        const __m128 values = _mm_loadu_ps (src + i);
        const __m128 gt     = _mm_cmp_ps   (values, maxvalues, _CMP_GT_OQ);
        maxindices          = _mm_blendv_epi8(maxindices, indices, _mm_castps_si128(gt));
        maxvalues           = _mm_max_ps   (values, maxvalues);
    }

    float   values_array [simd];
    int32_t indices_array[simd];

    _mm_storeu_ps   (           values_array,  maxvalues);
    _mm_storeu_si128( (__m128i*)indices_array, maxindices);

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
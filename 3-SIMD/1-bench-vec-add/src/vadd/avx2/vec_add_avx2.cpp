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
#include "vec_add_avx2.hpp"
#ifdef __AVX2__
/*
 *
 *
 *##############################################################################
 *
 *
 */
void vec_add_avx2(
              float* __restrict dst,
        const float* __restrict src_1,
        const float* __restrict src_2,
        const int               length)
{
    const int simd  = sizeof(__m256) / sizeof(float);
    const int first = length & ~(simd - 1);

    //
    // processing the data set 4 elements by 4 elements
    //

    for(int x = 0; x < first; x += simd)
    {
        const __m256 a = _mm256_loadu_ps( src_1 + x );
        const __m256 b = _mm256_loadu_ps( src_2 + x );

        const __m256 c = _mm256_add_ps(a, b);

        _mm256_storeu_ps( dst + x, c );
    }

    //
    // processing the rest of the elements
    //
    for (int i = first; i < length; i+= 1)
    {
        dst[i] = src_1[i] + src_2[i];
    }

};
/*
 *
 *
 *##############################################################################
 *
 *
 */
#endif
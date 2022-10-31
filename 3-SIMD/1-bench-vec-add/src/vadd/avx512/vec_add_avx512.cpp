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
#include "vec_add_avx512.hpp"
#ifdef __AVX512F__  // INTEL 512 bits
/*
 *
 *
 *##############################################################################
 *
 *
 */
void vec_add_avx512(
              float* __restrict dst,
        const float* __restrict src_1,
        const float* __restrict src_2,
        const int               length)
{
    const int simd  = sizeof(__m512) / sizeof(float);
    const int first = length & (simd - 1);

    //
    // processing the data set 4 elements by 4 elements
    //

    for(int x = 0; x < first; x += simd)
    {
        const __m512 a = _mm512_loadu_ps( src_1 + x );
        const __m512 b = _mm512_loadu_ps( src_2 + x );

        const __m512 c = _mm512_add_ps(a, b);

        _mm512_storeu_ps( dst + x, c );
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
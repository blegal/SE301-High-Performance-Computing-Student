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
#include "vec_max_avx2.hpp"
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
float vec_max_avx2(
        const float* __restrict src,
        const int               length)
{
    const int simd  = sizeof(__m256) / sizeof(float);
    const int first = length & ~(simd - 1);

    //
    // processing the data set 4 elements by 4 elements
    //
	__m256 max = _mm256_loadu_ps(src);
	for (int i = 0; i < first; i+= simd)
    {
		const __m256 value = _mm256_loadu_ps(src + i);
		max = _mm256_max_ps(value,  max);
	}

    //
    // Réduction des données temporaires en mode AVX2
    //

	const __m256 temp1 = _mm256_shuffle_ps(max, max, _MM_SHUFFLE(1, 0, 3, 2));
	const __m256 temp2 = _mm256_max_ps(max, temp1);
	const __m256 temp3 = _mm256_shuffle_ps(temp2, temp2, _MM_SHUFFLE(2, 3, 0, 1));
	const __m256 temp4 = _mm256_max_ps(temp3, temp2);
	const __m256 temp5 = _mm256_permute2f128_ps( temp4, temp4, 0x01 );
	const __m256 temp6 = _mm256_max_ps(temp4, temp5);

	const __m128 smax  = _mm256_extractf128_ps(temp6, 0);
	float maxvalue     = _mm_cvtss_f32( smax );

    //
    // On finit la fin de la réduction en mode scalaire
    //
    for (int i = first; i < length; i+= 1)
    {   
        maxvalue = std::fmax( maxvalue, src[i]);
    }

    return maxvalue;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
#endif
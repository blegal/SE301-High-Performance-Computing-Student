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
#include "vec_max_sse4.hpp"
#include <cstdint>
#include <cstdio>
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
float vec_max_sse4(
        const float* __restrict src,
        const int               length)
{
    const int simd  = sizeof(__m128) / sizeof(float);
    const int first = length & ~(simd - 1);

	__m128 maxs = _mm_loadu_ps(src);
	for (int i = 1; i < first; i+= simd)
    {
		const __m128 value = _mm_loadu_ps(src + i);
		maxs = _mm_max_ps(value, maxs);
	}

    //
    // Réduction des données temporaires en mode AVX2
    //

	const __m128 temp1 = _mm_shuffle_ps(maxs, maxs, _MM_SHUFFLE(1, 0, 3, 2));
	const __m128 temp2 = _mm_max_ps(maxs, temp1);
    const __m128 temp3 = _mm_shuffle_ps(temp2, temp2, _MM_SHUFFLE(2, 3, 0, 1));
	const __m128 temp4 = _mm_max_ps(temp3, temp2);
	float vmax = _mm_cvtss_f32(temp4);

    //
    // On finit la fin de la réduction en mode scalaire
    //
    for (int i = first; i < length; i+= 1)
    {
        vmax = std::fmax(vmax, src[i]);
    }

    return vmax;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
#endif
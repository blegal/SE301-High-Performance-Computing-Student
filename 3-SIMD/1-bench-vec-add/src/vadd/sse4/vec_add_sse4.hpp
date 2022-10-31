/**
  Copyright (c) 2012-2020 "Bordeaux INP, Bertrand LE GAL"
  bertrand.legal@ims-bordeaux.fr
  [http://legal.vvv.enseirb-matmeca.fr]

  This file is part of a LDPC library for realtime LDPC decoding
  on processor cores.
*/

#ifndef _vec_add_sse4_
#define	_vec_add_sse4_
#ifdef __SSE4_2__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <immintrin.h>

extern void vec_add_sse4(float* __restrict dst, const float* __restrict src_1, const float* __restrict src_2, const int32_t length);;

#endif // __SSE4_2__
#endif


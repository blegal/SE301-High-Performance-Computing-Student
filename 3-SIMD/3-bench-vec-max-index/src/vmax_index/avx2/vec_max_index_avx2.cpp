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
        return 0;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
#endif
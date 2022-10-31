/**
  Copyright (c) 2012-2020 "Bordeaux INP, Bertrand LE GAL"
  bertrand.legal@ims-bordeaux.fr
  [http://legal.vvv.enseirb-matmeca.fr]

  This file is part of a LDPC library for realtime LDPC decoding
  on processor cores.
*/

#ifndef _vec_max_avx2_
#define	_vec_max_avx2_
#ifdef __AVX2__

extern float vec_max_avx2(const float* __restrict src, const int length);

#endif // __AVX2__
#endif	/* _uchar_transpose_sse4_ */


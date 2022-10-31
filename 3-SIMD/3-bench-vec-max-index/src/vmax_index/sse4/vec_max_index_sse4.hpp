/**
  Copyright (c) 2012-2020 "Bordeaux INP, Bertrand LE GAL"
  bertrand.legal@ims-bordeaux.fr
  [http://legal.vvv.enseirb-matmeca.fr]

  This file is part of a LDPC library for realtime LDPC decoding
  on processor cores.
*/

#ifndef _vec_max_index_sse4_
#define	_vec_max_index_sse4_
#ifdef __SSE4_2__

extern int vec_max_index_sse4(const float* __restrict src, const int length);

#endif // __SSE4_2__
#endif


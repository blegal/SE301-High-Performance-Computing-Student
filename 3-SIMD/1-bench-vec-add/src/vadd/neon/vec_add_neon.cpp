/*
*	Optimized byte interleaving functions - Copyright (c) 2021 Bertrand LE GAL
*
*  This software is provided 'as-is', without any express or
*  implied warranty. In no event will the authors be held
*  liable for any damages arising from the use of this software.
*
*  Permission is granted to anyone to use this software for any purpose,
*  including commercial applications, and to alter it and redistribute
*  it freely, subject to the following restrictions:
*
*  1. The origin of this software must not be misrepresented;
*  you must not claim that you wrote the original software.
*  If you use this software in a product, an acknowledgment
*  in the product documentation would be appreciated but
*  is not required.
*
*  2. Altered source versions must be plainly marked as such,
*  and must not be misrepresented as being the original software.
*
*  3. This notice may not be removed or altered from any
*  source distribution.
*
*/

#include "vec_add_neon.hpp"
#if defined(__ARM_NEON__) || defined(__ARM_NEON)
/*
 *
 *
 *##############################################################################
 *
 *
 */
void vec_add_neon(
              float* __restrict dst,
        const float* __restrict src_1,
        const float* __restrict src_2,
        const int               length)
{
    const int simd  = sizeof(float32x4_t) / sizeof(float);
    const int first = length & ~(simd - 1);

    //
    // processing the data set 4 elements by 4 elements
    // 

    for(int x = 0; x < first; x += simd)
    {
        const float32x4_t a = vld1q_f32(src_1 + x);
        const float32x4_t b = vld1q_f32(src_2 + x);

        const float32x4_t c = vaddq_f32(a, b);

        vst1q_f32( (dst + x), c );
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

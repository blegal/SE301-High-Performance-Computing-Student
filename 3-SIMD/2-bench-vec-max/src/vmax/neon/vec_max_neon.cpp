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

#include "vec_max_neon.hpp"
#if defined(__ARM_NEON__) || defined(__ARM_NEON)
/*
 *
 *
 *##############################################################################
 *
 *
 */
float vec_max_neon(
        const float* __restrict src,
        const int               length)
{
    const int simd  = sizeof(float32x4_t) / sizeof(float);
    const int first = length & ~(simd - 1);

    //
    // processing the data set 4 elements by 4 elements
    // 
    float32x4_t maxvalues  = vld1q_f32(src);

    for(int x = simd; x < first; x += simd)
    {
        const float32x4_t a = vld1q_f32(src + x);
        maxvalues           = vmaxq_f32(a, maxvalues);
    }

    float   varray [4];
    vst1q_f32(values_array,  maxvalues);

    //
    // On finit la réduction des maxs
    //

    float max1 =  std::fmax( varray[0], varray[1]);
    float max2 =  std::fmax( varray[2], varray[3]);
    float maxv =  std::fmax(      max1,      max2);

    //
    // On finit la fin de la réduction en mode scalaire
    //
    for (int i = first; i < length; i+= 1)
    {   
        maxv = std::fmax( maxv, src[i]);
    }
    return maxv;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
 #endif

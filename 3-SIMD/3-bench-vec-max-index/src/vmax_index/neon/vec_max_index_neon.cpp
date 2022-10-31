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

#include "vec_max_index_neon.hpp"
#if defined(__ARM_NEON__) || defined(__ARM_NEON)
/*
 *
 *
 *##############################################################################
 *
 *
 */
int vec_max_index_neon_old(
        const float* __restrict src,
        const int               length)
{
    const int simd  = sizeof(float32x4_t) / sizeof(float);
    const int first = length & ~(simd - 1);

    const int32x4_t increment  = { 4, 4, 4, 4 };
          int32x4_t indices    = { 0, 1, 2, 3 };
          int32x4_t maxindices = indices;
        float32x4_t maxvalues  = vld1q_f32( src );

    for (int i = simd; i < first; i += simd) {

        indices = vaddq_s32(indices, increment);
        const float32x4_t values = vld1q_f32(src + i);
        const uint32x4_t  gt     = vcgtq_f32(values, maxvalues);
        maxindices               = vbslq_f32(gt, indices, maxindices);
        maxvalues                = vmaxq_f32(values, maxvalues);
    }

    float   values_array [simd];
    int32_t indices_array[simd];

    vst1q_f32(values_array,  maxvalues);
    vst1q_s32(indices_array, maxindices);

    int   maxindex = indices_array[0];
    float maxvalue =  values_array[0];

#pragma unroll
    for (int i = 1; i < simd; i++)
    {
        if (values_array[i] > maxvalue)
        {
            maxvalue = values_array [i];
            maxindex = indices_array[i]; 
        }
        else if( values_array[i] == maxvalue )
        {
            if( maxindex > indices_array[i] )
            {
                maxvalue = values_array [i];
                maxindex = indices_array[i];
            }
        }
    }
    return maxindex;
};

template<int length>
int t_vec_max_index_neon(const float* __restrict src)
{
    constexpr int simd = sizeof(float32x4_t) / sizeof(float);

    const int32x4_t increment  = { 4, 4, 4, 4 };
          int32x4_t indices    = { 0, 1, 2, 3 };
          int32x4_t maxindices = indices;
        float32x4_t maxvalues  = vld1q_f32( src );

    for (int i = simd; i < length; i += simd) {

        indices = vaddq_s32(indices, increment);
        const float32x4_t values = vld1q_f32(src + i);
        const uint32x4_t  gt     = vcgtq_f32(values, maxvalues);
        maxindices               = vbslq_f32(gt, indices, maxindices);
//      maxvalues                = vmaxq_f32(values, maxvalues);
        maxvalues                = vbslq_f32(gt, values, maxvalues);
    }

    float   values_array [simd];
    int32_t indices_array[simd];

    vst1q_f32(values_array,  maxvalues);
    vst1q_s32(indices_array, maxindices);

    int   maxindex = indices_array[0];
    float maxvalue =  values_array[0];

#pragma unroll
    for (int i = 1; i < simd; i++)
    {
        if (values_array[i] > maxvalue)
        {
            maxvalue = values_array [i];
            maxindex = indices_array[i]; 
        }
    }
    return maxindex;
};
    
int vec_max_index_neon(
        const float* __restrict src,
        const int               length)
{
         if(length ==    32) return t_vec_max_index_neon<   32>(src);
    else if(length ==    64) return t_vec_max_index_neon<   64>(src);
    else if(length ==   128) return t_vec_max_index_neon<  128>(src);
    else if(length ==   256) return t_vec_max_index_neon<  256>(src);
    else if(length ==   512) return t_vec_max_index_neon<  512>(src);
    else if(length ==  1024) return t_vec_max_index_neon< 1024>(src);
    else if(length ==  2048) return t_vec_max_index_neon< 2048>(src);
    else if(length ==  4096) return t_vec_max_index_neon< 4096>(src);
    else if(length ==  8192) return t_vec_max_index_neon< 8192>(src);
    else if(length == 16384) return t_vec_max_index_neon<16384>(src);
    else if(length == 32768) return t_vec_max_index_neon<32768>(src);
    else
    return vec_max_index_neon_old(src, length);
}
/*
 *
 *
 *##############################################################################
 *
 *
 */
 #endif

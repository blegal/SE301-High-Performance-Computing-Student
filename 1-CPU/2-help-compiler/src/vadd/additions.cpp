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

#include "additions.hpp"
/*
 *
 *
 *##############################################################################
 *
 *
 */
float vec_sum (
        const float* __restrict src_1,
        const int               length)
{
    float accu = 0;
#if defined (__clang__)
    #pragma clang loop vectorize(disable)
#endif
    for (int i = 0; i < length; i+= 1)
    {
       accu += src_1[i];
    }
    return accu;
}
/*
 *
 *
 *##############################################################################
 *
 *
 */
void vec_add (
              float* __restrict dst,
        const float* __restrict src_1,
        const float* __restrict src_2,
        const int               length)
{
#if defined (__clang__)
    #pragma clang loop vectorize(disable)
#endif
    for (int i = 0; i < length; i+= 1)
    {
       dst[i] = src_1[i] + src_2[i];
    }
}
/*
 *
 *
 *##############################################################################
 *
 *
 */
void vec_add_unroll (
              float* __restrict dst,
        const float* __restrict src_1,
        const float* __restrict src_2,
        const int               length)
{
#if defined (__clang__)
    #pragma clang loop vectorize(disable)
#endif
    for (int i = 0; i < length; i+= 8)
    {
       dst[i  ] = src_1[i  ] + src_2[i  ];
       dst[i+1] = src_1[i+1] + src_2[i+1];
       dst[i+2] = src_1[i+2] + src_2[i+2];
       dst[i+3] = src_1[i+3] + src_2[i+3];
       dst[i+4] = src_1[i+4] + src_2[i+4];
       dst[i+5] = src_1[i+5] + src_2[i+5];
       dst[i+6] = src_1[i+6] + src_2[i+6];
       dst[i+7] = src_1[i+7] + src_2[i+7];
    }
}
/*
 *
 *
 *##############################################################################
 *
 *
 */
float vec_sum_unroll(
        const float* __restrict src_1,
        const int               length)
{
    float accu = 0;
#if defined (__clang__)
    #pragma clang loop vectorize(disable)
#endif
    for (int i = 0; i < length; i+= 8)
    {
       float a1 = src_1[i + 0] + src_1[ i + 1];
       float a2 = src_1[i + 2] + src_1[ i + 3];
       float a3 = src_1[i + 4] + src_1[ i + 5];
       float a4 = src_1[i + 6] + src_1[ i + 7];
       accu    += (a1 + a2) + (a3 + a4);
    }
    return accu;
}
/*
 *
 *
 *##############################################################################
 *
 *
 */

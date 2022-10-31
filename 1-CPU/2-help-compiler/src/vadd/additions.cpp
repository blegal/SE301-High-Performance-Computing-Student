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
    for (int i = 0; i < length; i+= 1)
    {
       dst[i  ] = src_1[i  ] + src_2[i  ];
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
    for (int i = 0; i < length; i+= 1)
    {
       float a = src_1[i];
       accu   += a;
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

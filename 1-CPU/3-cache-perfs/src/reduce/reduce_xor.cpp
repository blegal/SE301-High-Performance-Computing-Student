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

#include "reduce_xor.hpp"
/*
 *
 *
 *##############################################################################
 *
 *
 */
#if !defined (__clang__)
    __attribute__((optimize("no-tree-vectorize")))
#endif
int32_t reduction_xor_stride(
        const int32_t* src,
        const int32_t step,
        const int32_t length)
{
    int32_t resu = 0;
    for (int s = 0; s < step; s += 1)
    {
        for (int x = s; x < length; x += step)
        {
            resu ^= src[x];
        }
    }
    return resu;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
#if !defined (__clang__)
    __attribute__((optimize("no-tree-vectorize")))
#endif
int8_t reduction_xor_stride(
        const int8_t* src,
        const int32_t step,
        const int32_t length)
{
    int8_t resu = 0;
    for (int s = 0; s < step; s += 1)
    {
        for (int x = s; x < length; x += step)
        {
            resu ^= src[x];
        }
    }
    return resu;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */

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

#include "vec_sum_cond.hpp"
/*
 *
 *
 *##############################################################################
 *
 *
 */
float vec_sum_cond(
        const float* src_1,
        const int               length)
{
    float accu = 0;
    for (int i = 0; i < length; i+= 1)
    {
        if( src_1[i] > 0.0f )
            accu += src_1[i];
        else
            accu -= src_1[i];
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
float vec_sum_cond_hard(
        const float* src_1,
        const int               length)
{
    float accu = 0;
    for (int i = 0; i < length; i+= 1)
    {
        if( src_1[i] < -100.0f )
            accu += (src_1[i] + 50.0f);

        else if( src_1[i] < -10.0f )
            accu += (src_1[i] - 2.0f);

        else if( src_1[i] < 0.0f )
            accu += (src_1[i] + 1.0f );

        else if( src_1[i] < 10.0f )
            accu += (src_1[i] - 2.0f);

        else if( src_1[i] < 100.0f )
            accu += src_1[i];

        else if( src_1[i] > +100.0f )
            accu += (src_1[i] -50.0f);

        else
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
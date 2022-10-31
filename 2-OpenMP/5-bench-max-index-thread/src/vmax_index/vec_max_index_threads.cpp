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

#include <cfloat>
#include <climits>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <thread>

/*
 *
 *
 *##############################################################################
 *
 *
 */
int vec_max_index_x86(
        const float* __restrict src,
        const int               length)
{
    float maxv = -FLT_MAX;
    int index  =        0;
    for (int i = 0; i < length; i+= 1)
    {
        if( src[i] > maxv )
        {
            maxv  = src[i];
            index = i;
        }
    }
    return index;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
static void thread_vec_max_index(
    const float* src,
    const int start,
    const int stop,
    float* maxv,
    int*   idx)
{
    (*maxv) = src[start];  //
    (*idx)  = start;       //

    for (int i = start; i < stop; i+= 1)
    {
        if( src[i] > (*maxv) )
            {
                (*maxv)  = src[i];
                (*idx)   = i;
            }
        }
}
/*
 *
 *
 *##############################################################################
 *
 *
 */

int vec_max_index_threads(
        const float* __restrict src,
        const int               length,
        const int               nThreads)
{
    float         priv_maxv[nThreads];
    int           priv_idx [nThreads];

    int step = length / nThreads;

    std::thread t [nThreads];

    //
    // On cree les thread qui sont automatiquement lancés
    //

    for (int i = 0; i < length; i += step)
    {
        t[i/step] = std::thread(
            thread_vec_max_index, src,
            i, i + step,
            priv_maxv + (i/step),     // PAS de passage par REF sinon std::ref()
            priv_idx  + (i/step)      // PAS de passage par REF sinon std::ref()
            );
    }

    //
    // On attend que tous les threads aient terminé
    //

    for (int i = 0; i < nThreads; ++i)
    {
        t[i].join();
    }

    //
    // On fait la fusion des résultats
    //

    float maxv = priv_maxv[0];
    int index  = priv_idx [0];
    for (int i = 1; i < nThreads; ++i)
    {
        if(priv_maxv[i] > maxv)
        {
            maxv  = priv_maxv[i];
            index = priv_idx [i];
        }
        else if( (priv_maxv[i] == maxv) && (priv_idx[i] < index) )
        {
            maxv  = priv_maxv[i];
            index = priv_idx [i];
        }
    }

    return index;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */
int vec_max_index_x86_novect(
        const float* __restrict src,
        const int32_t length)
{
    float maxv = -FLT_MAX;
    int index  =        0;
#if defined (__clang__)
    #pragma clang loop vectorize(disable)
#endif
    for (int i = 0; i < length; i+= 1)
    {
        if( src[i] > maxv )
        {
            maxv  = src[i];
            index = i;
        }
    }
    return index;
};
/*
 *
 *
 *##############################################################################
 *
 *
 */

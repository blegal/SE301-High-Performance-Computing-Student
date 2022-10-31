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

#include "add/additions.hpp"

#include <cstring>
#include <chrono>
#include <random>

/*
 *
 *
 *##############################################################################
 *
 *
 */

void header( )
{
    printf("(II)\n");
#if defined (__APPLE__)
    printf("(II) Stage 1 - The compiler, your friend on MacOS\n");
#elif defined (__linux__)    
    printf("(II) Stage 1 - The compiler, your friend on Linux\n");
#else
    printf("(II) Stage 1 - The compiler, your friend on Windows\n");
#endif
    printf("(II) Bertrand LE GAL - bertrand.legal@enseirb-matmeca.fr\n");
    printf("(II)\n");

#if defined (__clang__)    
    printf("(II) Code compiled with LLVM (%d.%d.%d) ", __clang_major__, __clang_minor__, __clang_patchlevel__);
#elif defined (__GNUC__)
    printf("(II) Code compiled with GCC (%d.%d.%d) ", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#else
    printf("(II) Code compiled with UNKWON compiler ");
#endif
    printf("the %s at %s\n", __DATE__, __TIME__);
    printf("(II)\n");
}

/*
 *
 *
 *##############################################################################
 *
 *
 */

int main(int argc, char* argv[])
{

    header();

    const int v_begin =     128; // 1024;
    const int v_end   =   65536; // 64M elements
    const int v_step  =       2;
    float accu = 0.f;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.f, +10.f);

   /*
    *
    *
    *##############################################################################
    *
    *
    */

    int nTest = 4 * 8388608;


    for(int buffSize = v_begin; buffSize <= v_end; buffSize *= v_step)
    {
             if( buffSize <      1024 ) printf("  #elements [%4d e ]  |  Vector add  |  ", (buffSize) );
        else if( buffSize < 1024*1024 ) printf("  #elements [%4d k ]  |  Vector add  |  ", (buffSize) / 1024 );
        else                            printf("  #elements [%4d M ]  |  Vector add  |  ", (buffSize) / 1024 / 1024 );

        float* a_tab  = new float[buffSize];
        float* b_tab  = new float[buffSize];
        float* c_tab  = new float[buffSize];

        for (int i = 0; i < buffSize; i += 1)
        {
            a_tab[i] = dis(gen);
            b_tab[i] = dis(gen);
        }

        //
        // PROCEDURE DE TEST SUR LES CODE NON-OPTIMISES
        //

        auto start_i_ref = std::chrono::system_clock::now();
        for(int32_t loop = 0; loop < nTest; loop += 1)
            vec_add(c_tab, a_tab, b_tab, buffSize);
        auto stop_i_ref = std::chrono::system_clock::now();

        const uint64_t time_ref = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_ref - start_i_ref).count() / nTest;
        printf("Average [%8d ns / exec ]  |  Average [ %1.3f ns / data ]\n", (int32_t)time_ref, (time_ref/(float)buffSize));

        delete[] a_tab;
        delete[] b_tab;
        delete[] c_tab;

        nTest /= 2;
    }
    printf("\n");

   /*
    *
    *
    *##############################################################################
    *
    *
    */

    nTest = 4 * 8388608;

    for(int buffSize = v_begin; buffSize <= v_end; buffSize *= v_step)
    {
             if( buffSize <      1024 ) printf("  #elements [%4d e ]  |  Vector sum  |  ", (buffSize) );
        else if( buffSize < 1024*1024 ) printf("  #elements [%4d k ]  |  Vector sum  |  ", (buffSize) / 1024 );
        else                            printf("  #elements [%4d M ]  |  Vector sum  |  ", (buffSize) / 1024 / 1024 );


        float* a_tab  = new float[buffSize];

        for (int i = 0; i < buffSize; i += 1)
        {
          a_tab[i] = ((float)(rand()%256)) / 256.0f - 0.50f;
        }

        //
        // PROCEDURE DE TEST SUR LES CODE NON-OPTIMISES
        //

        auto start_i_ref = std::chrono::system_clock::now();
        for(int32_t loop = 0; loop < nTest; loop += 1)
            accu += vec_sum(a_tab, buffSize);
        auto stop_i_ref = std::chrono::system_clock::now();

        const uint64_t time_ref = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_ref - start_i_ref).count() / nTest;
        printf("Average [%8d ns / exec ]  |  Average [ %1.3f ns / data ]\n", (int32_t)time_ref, (time_ref/(float)buffSize));

        delete[] a_tab;

        nTest /= 2;

    }
    printf("\n");

   /*
    *
    *
    *##############################################################################
    *
    *
    */

    return (accu != 0.0f) ? EXIT_SUCCESS : EXIT_FAILURE; // to avoid compiler optimizations
}
    
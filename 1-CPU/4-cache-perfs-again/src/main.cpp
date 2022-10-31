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

#include "reduce/reduce_sum.hpp"
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
    printf("(II) Stage 4 - 2d array so fun to access and so bad for performances on MacOS\n");
#elif defined (__linux__)    
    printf("(II) Stage 4 - 2d array so fun to access and so bad for performances on Linux\n");
#else
    printf("(II) Stage 4 - 2d array so fun to access and so bad for performances on Windows\n");
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

    const int v_begin =     16; // 1024;
    const int v_end   =  32768; // 64M elements
    const int v_step  =      2;

    float h_sum  = 0.f; // to avoid compiler optimizations
    float v_sum  = 0.f; // to avoid compiler optimizations
    int nTest;

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

    printf("(II)\n");
    printf("(II) Evaluation of 2d matrix sum - float - horizontal access\n");
    printf("(II)\n");

    nTest = 4194304;

    for(int buffSize = v_begin; buffSize <= v_end; buffSize *= v_step)
    {
             if( buffSize <      1024 ) printf(" %4d e | ", (buffSize) );
        else if( buffSize < 1024*1024 ) printf(" %4d k | ", (buffSize) / 1024 );
        else                            printf(" %4d M | ", (buffSize) / 1024 / 1024 );

        float** a_tab  = new float*[buffSize];
        for(int y = 0; y < buffSize; y += 1)
        {
            a_tab[y]  = new float[buffSize];
            for (int x = 0; x < buffSize; x += 1)
            {
                a_tab[y][x] = dis(gen);
            }

        }

        auto start_i_omp = std::chrono::system_clock::now();
        for(int loop = 0; loop < nTest; loop += 1)
            h_sum += reduce_sum_h(a_tab, buffSize, buffSize);
        auto stop_i_omp = std::chrono::system_clock::now();

        const uint64_t time_omp = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_omp - start_i_omp).count() / nTest;
        printf(" %10d ns/exec | %1.3f ns/data\n", (int)time_omp, (time_omp/(float)buffSize)/(float)buffSize);

        nTest /= 4;

        for(int y = 0; y < buffSize; y += 1)
            delete[] a_tab[y];
        delete[] a_tab;
    }
    printf("\n");


   /*
    *
    *
    *##############################################################################
    *
    *
    */

    printf("(II)\n");
    printf("(II) Evaluation of 2d matrix sum - float - vertical access\n");
    printf("(II)\n");

    nTest = 4194304;

    for(int buffSize = v_begin; buffSize <= v_end; buffSize *= v_step)
    {
             if( buffSize <      1024 ) printf(" %4d e | ", (buffSize) );
        else if( buffSize < 1024*1024 ) printf(" %4d k | ", (buffSize) / 1024 );
        else                            printf(" %4d M | ", (buffSize) / 1024 / 1024 );

        float** a_tab  = new float*[buffSize];
        for(int y = 0; y < buffSize; y += 1)
        {
            a_tab[y]  = new float[buffSize];
            for (int x = 0; x < buffSize; x += 1)
            {
                a_tab[y][x] = rand();
            }
        }

        auto start_i_omp = std::chrono::system_clock::now();
        for(int loop = 0; loop < nTest; loop += 1)
            v_sum += reduce_sum_v(a_tab, buffSize, buffSize);
        auto stop_i_omp = std::chrono::system_clock::now();

        const uint64_t time_omp = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_omp - start_i_omp).count() / nTest;
        printf(" %10d ns/exec | %1.3f ns/data\n", (int)time_omp, (time_omp/(float)buffSize)/(float)buffSize);

        nTest /= 4;

        for(int y = 0; y < buffSize; y += 1)
            delete[] a_tab[y];
        delete[] a_tab;
    }
    printf("\n");

   /*
    *
    *
    *##############################################################################
    *
    *
    */

    return (h_sum == v_sum) ? EXIT_SUCCESS : EXIT_FAILURE; // to avoid compiler optimizations
}
    
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

#include "reduce/reduce_xor.hpp"
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
    printf("(II) Stage 3 - Evaluate memory access patterns on performances on MacOS\n");
#elif defined (__linux__)    
    printf("(II) Stage 3 - Evaluate memory access patterns on performances on Linux\n");
#else
    printf("(II) Stage 3 - Evaluate memory access patterns on performances on Windows\n");
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

    const int v_begin =           128; // 1024;
    const int v_end   =  64 * 1048576; // 64M elements
    const int v_step  =             2;
    const int max_stride = 256;

    int32_t o_xor  = 0; // to avoid compiler optimizations
    int32_t s_xor  = 0; // to avoid compiler optimizations
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
    printf("(II) Evaluation done on byte (int8_t) values\n");
    printf("(II)\n");

    printf(" #chars | ");
    for (int stride = 1; stride <= max_stride; stride *= 2)
        printf(" %5d |", stride);
    printf("\n");

    nTest = 4 * 1048576;

    for(int buffSize = v_begin; buffSize <= v_end; buffSize *= v_step)
    {
             if( buffSize <      1024 ) printf(" %4d e | ", (buffSize) );
        else if( buffSize < 1024*1024 ) printf(" %4d k | ", (buffSize) / 1024 );
        else                            printf(" %4d M | ", (buffSize) / 1024 / 1024 );

        int8_t* a_tab  = new int8_t[buffSize];
        
        for (int i = 0; i < buffSize; i += 1)
        {
            a_tab[i] = dis(gen);
        }


        reduction_xor_stride(a_tab, 1, buffSize);

        for (int stride = 1; stride <= max_stride; stride *= 2)
        {
            auto start_i_omp = std::chrono::system_clock::now();
            for(int loop = 0; loop < nTest; loop += 1)
                s_xor |= reduction_xor_stride(a_tab, stride, buffSize);
            auto stop_i_omp = std::chrono::system_clock::now();

            const uint64_t time_omp = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_omp - start_i_omp).count() / nTest;
            printf(" %1.3f |", (time_omp/(float)buffSize));
        }
        printf("\n");

        nTest /= 2;
        
        delete[] a_tab;
    }


   /*
    *
    *
    *##############################################################################
    *
    *
    */

    printf("(II)\n");
    printf("(II) Evaluation done on interger (int) values\n");
    printf("(II)\n");

    printf("  #ints | ");
    for (int stride = 1; stride <= max_stride; stride *= 2)
        printf(" %5d |", stride);
    printf("\n");


    nTest = 4 * 1048576;

    for(int buffSize = v_begin; buffSize <= v_end; buffSize *= v_step)
    {
             if( buffSize <      1024 ) printf(" %4d e | ", (buffSize) );
        else if( buffSize < 1024*1024 ) printf(" %4d k | ", (buffSize) / 1024 );
        else                            printf(" %4d M | ", (buffSize) / 1024 / 1024 );

        int32_t* a_tab  = new int32_t[buffSize];
        
        for (int i = 0; i < buffSize; i += 1)
          a_tab[i] = rand();

        reduction_xor_stride(a_tab, 1, buffSize);

        for (int stride = 1; stride <= max_stride; stride *= 2)
        {
            auto start_i_omp = std::chrono::system_clock::now();
            for(int loop = 0; loop < nTest; loop += 1)
                s_xor |= reduction_xor_stride(a_tab, stride, buffSize);
            auto stop_i_omp = std::chrono::system_clock::now();

            const uint64_t time_omp = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_omp - start_i_omp).count() / nTest;
            printf(" %1.3f |", (time_omp/(float)buffSize));
        }
        printf("\n");

        nTest /= 2;
        
        delete[] a_tab;
    }

   /*
    *
    *
    *##############################################################################
    *
    *
    */

    return (s_xor== o_xor) ? EXIT_SUCCESS : EXIT_FAILURE; // to avoid compiler optimizations
}
    
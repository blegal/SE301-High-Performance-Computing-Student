/*
*  Teaching examples used to learn GPU and CUDA features for
*  scientific programmaing.
*
*  Copyright (c) 2022 Bertrand LE GAL
*  bertrand.legalenseirb-matmeca.fr
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

#include <iostream>
#include <omp.h>
#include "vmax/vec_max_x86.hpp"
#include "cuda/CUDAMax.hpp"
#include <cstring>
#include <chrono>
#include <random>


int main(int argc, char* argv[])
{

#if defined (__APPLE__)
    printf("(II) Stage 3 - Let's focus on other problematics on MacOS\n");
#elif defined (__linux__)    
    printf("(II) Stage 3 - Let's focus on other problematics on Linux\n");
#else
    printf("(II) Stage 3 - Let's focus on other problematics on a undefined platform\n");
#endif


#if defined (__clang__)    
    printf("(II) Code compiled with LLVM (%d.%d.%d)\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
#elif defined (__GNUC__)
    printf("(II) Code compiled with GCC (%d.%d.%d)\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#else
    printf("(II) Code compiled with UNKWON compiler\n");
#endif

    const int v_begin =           1024;
    const int v_end   =  256 * 1048576; // 64M elements
    const int v_step  =              2;

    for(int buffSize = v_begin; buffSize <= v_end; buffSize *= v_step)
    {
        const int nTest   =   (buffSize < 65536) ? 8192 : 1024;

        if( buffSize < 1024 )
            printf("+> #elements [%4d e] - nTests = %d\n", (buffSize), nTest );
        else if( buffSize < 1024*1024 )
            printf("+> #elements [%4d k] - nTests = %d\n", (buffSize) / 1024, nTest );
        else
            printf("+> #elements [%4d M] - nTests = %d\n", (buffSize) / 1024 / 1024, nTest );

        float* a_tab  = new float[buffSize];

        float o_nov;
        float o_x86;
        float o_omp;
        float o_mtl;

        //
        //  Random number generation for testing
        //

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-10.f, +10.f);


        for (int i = 0; i < buffSize; i += 1)
        {
            a_tab[i] = dis(gen);
        }

        //
        // PROCEDURE DE TEST SUR LES CODE NON-OPTIMISES
        //

        auto start_i_ref = std::chrono::system_clock::now();
        for(int32_t loop = 0; loop < nTest; loop += 1)
            o_nov = vec_max_x86_novect(a_tab, buffSize);
        auto stop_i_ref = std::chrono::system_clock::now();

        const uint64_t time_ref = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_ref - start_i_ref).count() / nTest;
        printf("    - [-x86-] unoptimized     \033[32mOK\033[0m [%8d ns]\n", (int32_t)time_ref);

        //
        // PROCEDURE DE TEST SUR LES CODE AUTO-OPTIMISES
        //

        auto start_i_x86 = std::chrono::system_clock::now();
        for(int32_t loop = 0; loop < nTest; loop += 1)
            o_x86 = vec_max_x86(a_tab, buffSize);
        auto stop_i_x86 = std::chrono::system_clock::now();

        const uint64_t time_x86 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_x86 - start_i_x86).count() / nTest;
        if( o_x86 == o_nov ){
            printf("    - [AUTOV] auto-vectorized \033[32mOK\033[0m [%8d ns]\n", (int32_t)time_x86);
        }else{
            printf("    - [AUTOV] auto-vectorized \033[31mKO\033[0m [%8d ns]\n", (int32_t)time_x86);
            exit( EXIT_FAILURE );
        }

        //
        // PROCEDURE DE TEST SUR LES CODES SSE4
        //
        const int max_threads = 4; //std::thread::hardware_concurrency();
        for (int threads = 1; threads <= max_threads; threads++)
        {
            //
            // Verify OpenMP code --------------------------------------------------------------
            //
            omp_set_num_threads(threads);

            auto start_i_omp = std::chrono::system_clock::now();
            for(int loop = 0; loop < nTest; loop += 1)
                o_omp = vec_max_omp(a_tab, buffSize);
            auto stop_i_omp = std::chrono::system_clock::now();

            const uint64_t time_omp = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_omp - start_i_omp).count() / nTest;
            if( o_x86 == o_omp ){
                printf("    - [OMP%2d] multi-core mode \033[32mOK\033[0m [%8d ns]\n", threads, (int32_t)time_omp);
            }else{
                printf("    - [OMP%2d] multi-core mode \033[31mKO\033[0m [%8d ns]\n", threads, (int32_t)time_omp);
                printf("o_x86 = %f\n", o_x86);
                printf("o_omp = %f\n", o_omp);
                exit( EXIT_FAILURE );
            }
        }

        CUDAMax c_max( buffSize );
        c_max.load(a_tab);
        auto start_i_mtl = std::chrono::system_clock::now();
        for(int32_t loop = 0; loop < nTest; loop += 1)
            c_max.execute();
        o_mtl = c_max.result();
        auto stop_i_mtl = std::chrono::system_clock::now();

        uint64_t time_mtl = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_mtl - start_i_mtl).count() / nTest;
        if( o_x86 == o_mtl ){
            printf("    - [ CUDA] many-core  mode \033[32mOK\033[0m [%8d ns]\n", (int32_t)time_mtl);
        }else{
            printf("    - [ CUDA] many-core  mode \033[31mKO\033[0m [%8d ns]\n", (int32_t)time_mtl);
            printf("o_x86 = %f\n", o_x86);
            printf("o_omp = %f\n", o_omp);
            printf("o_mtl = %f\n", o_mtl);
            exit( EXIT_FAILURE );
        }


        start_i_mtl = std::chrono::system_clock::now();
        for(int32_t loop = 0; loop < nTest; loop += 1)
        {
            c_max.load(a_tab);
            c_max.execute();
            o_mtl = c_max.result();
        }
        stop_i_mtl = std::chrono::system_clock::now();

        time_mtl = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_mtl - start_i_mtl).count() / nTest;
        if( o_x86 == o_mtl )
        {
            printf("    - [ CUDA] many-c. + DMA   \033[32mOK\033[0m [%8d ns]\n", (int32_t)time_mtl);
        }
        else
        {
            printf("    - [ CUDA] many-c. + DMA   \033[31mKO\033[0m [%8d ns]\n", (int32_t)time_mtl);
            exit( EXIT_FAILURE );
        }

        printf("\n");
        
        delete[] a_tab;
    }

    return EXIT_SUCCESS;
}

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

#include <iostream>
#include <omp.h>

#include "vadd/vec_add_x86.hpp"
#include "cuda/CUDAAdder.hpp"
#include <cstring>
#include <chrono>
#include <random>

bool is_ok(const float* ref, const float* eva, const int length)
{
    bool ok = true;
    for(int i = 0; i < length; i += 1)
    {
        if( eva[i] != ref[i] )
        {
            printf("i = %4d | eva[%f] != ref[%f]\n", i, eva[i], ref[i]);
            ok = false;
        }
    }
    return ok;
}


int main(int argc, char* argv[])
{

#if defined (__APPLE__)
    printf("(II) Stage 1 - The vector sum example like previously on MacOS\n");
#elif defined (__linux__)    
    printf("(II) Stage 1 - The vector sum example like previously on Linux\n");
#else
    printf("(II) Stage 1 - The vector sum example like previously on a undefined platform\n");
#endif


#if defined (__clang__)    
    printf("(II) Code compiled with LLVM (%d.%d.%d)\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
#elif defined (__GNUC__)
    printf("(II) Code compiled with GCC (%d.%d.%d)\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#else
    printf("(II) Code compiled with UNKWON compiler\n");
#endif

    const int v_begin =          65536; // 1024;
    const int v_end   =    2 * 1048576; // 2M elements
    const int v_step  =              2;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.f, +10.f);

    for(int buffSize = v_begin; buffSize <= v_end; buffSize *= v_step)
    {
        if( buffSize < 1024 )
            printf("+> #elements [%4d e]\n", (buffSize) );
        else if( buffSize < 1024*1024 )
            printf("+> #elements [%4d k]\n", (buffSize) / 1024 );
        else
            printf("+> #elements [%4d M]\n", (buffSize) / 1024 / 1024 );

        int nTest   =     (buffSize < 1024*1024)    ? 65536 : 1024;
            nTest   =     (buffSize < 65536)        ? 65536 : 4096;

        float* a_tab  = new float[buffSize];
        float* b_tab  = new float[buffSize];

        float* o_nov  = new float[buffSize];
        float* o_x86  = new float[buffSize];
        float* o_omp  = new float[buffSize];
        float* o_mtl  = new float[buffSize];
        
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
            vec_add_x86_novect(o_nov, a_tab, b_tab, buffSize);
        auto stop_i_ref = std::chrono::system_clock::now();

        const uint64_t time_ref = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_ref - start_i_ref).count() / nTest;
        printf("    - [-x86-] unoptimized     \033[32mOK\033[0m [%8d ns]\n", (int32_t)time_ref);

        //
        // PROCEDURE DE TEST SUR LES CODE AUTO-OPTIMISES
        //

        auto start_i_x86 = std::chrono::system_clock::now();
        for(int32_t loop = 0; loop < nTest; loop += 1)
            vec_add_x86(o_x86, a_tab, b_tab, buffSize);
        auto stop_i_x86 = std::chrono::system_clock::now();

        const uint64_t time_x86 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_x86 - start_i_x86).count() / nTest;
        printf("    - [AUTOV] auto-vectorized \033[32mOK\033[0m [%8d ns]\n", (int32_t)time_x86);

        //
        // PROCEDURE DE TEST SUR LES CODES SSE4
        //
        const int max_threads = 4;//std::thread::hardware_concurrency();
        for (int nThreads = 1; nThreads <= max_threads; nThreads += 1)
        {
            //
            // Verify OpenMP code --------------------------------------------------------------
            //
            omp_set_num_threads(nThreads);

            auto start_i_omp = std::chrono::system_clock::now();
            for(int loop = 0; loop < nTest; loop += 1)
                vec_add_omp(o_omp, a_tab, b_tab, buffSize);
            auto stop_i_omp = std::chrono::system_clock::now();

            const uint64_t time_omp = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_omp - start_i_omp).count() / nTest;
            if( is_ok(o_x86, o_omp, buffSize) ){
                printf("    - [OMP%2d] multi-core mode \033[32mOK\033[0m [%8d ns]\n", nThreads, (int32_t)time_omp);
            }else{
                printf("    - [OMP%2d] multi-core mode \033[31mKO\033[0m [%8d ns]\n", nThreads, (int32_t)time_omp);
                exit( EXIT_FAILURE );
            }
        }

        CUDAAdder madd( buffSize );
        madd.load_A(a_tab);
        madd.load_B(b_tab);
        auto start_i_mtl = std::chrono::system_clock::now();
        for(int32_t loop = 0; loop < nTest; loop += 1)
            madd.execute();
        madd.store_C(o_mtl);
        auto stop_i_mtl = std::chrono::system_clock::now();

        uint64_t time_mtl = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_mtl - start_i_mtl).count() / nTest;
        if( is_ok(o_x86, o_mtl, buffSize) ){
            printf("    - [ CUDA] many-core  mode \033[32mOK\033[0m [%8d ns]\n", (int32_t)time_mtl);
        }else{
            printf("    - [ CUDA] many-core  mode \033[31mKO\033[0m [%8d ns]\n", (int32_t)time_mtl);
            exit( EXIT_FAILURE );
        }


        start_i_mtl = std::chrono::system_clock::now();
        for(int32_t loop = 0; loop < nTest; loop += 1)
        {
            madd.load_A(a_tab);
            madd.load_B(b_tab);
            madd.execute();
            madd.store_C(o_mtl);
        }
        stop_i_mtl = std::chrono::system_clock::now();

        time_mtl = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_mtl - start_i_mtl).count() / nTest;
        if( is_ok(o_x86, o_mtl, buffSize) )
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
        delete[] b_tab;
        delete[] o_nov;
        delete[] o_x86;
        delete[] o_omp;
        delete[] o_mtl;
    }

    return EXIT_SUCCESS;
}
    
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

#include "tools.hpp"
#include "vmax_index/x86/vec_max_index_x86.hpp"
#include "vmax_index/neon/vec_max_index_neon.hpp"
#include "vmax_index/sse4/vec_max_index_sse4.hpp"
#include "vmax_index/avx2/vec_max_index_avx2.hpp"

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
    printf("(II) Stage 3 - One more time on MacOS\n");
#elif defined (__linux__)    
    printf("(II) Stage 3 - One more time on Linux\n");
#else
    printf("(II) Stage 3 - One more time on a undefined platform\n");
#endif


#if defined (__clang__)    
    printf("(II) Code compiled with LLVM (%d.%d.%d)\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
#elif defined (__GNUC__)
    printf("(II) Code compiled with GCC (%d.%d.%d)\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#else
    printf("(II) Code compiled with UNKWON compiler\n");
#endif

    const int v_begin =      32;//1024;
    const int v_end   =   1048576;
    const int v_step  =         2;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-10.f, +10.f);

    for(int buffSize = v_begin; buffSize <= v_end; buffSize *= v_step)
    {
        printf("+> memory size [%4d kB - %4d elements]\n", ((int)sizeof(float) * buffSize) / 1024, buffSize);
        int nTest   =     (buffSize < 1024*1024)    ? 65536 : 1024;
            nTest   =     (buffSize < 65536)        ? 65536 : 4096;

        float* a_tab  = new float[buffSize];
        

        for (int i = 0; i < buffSize; i += 1)
        {
            a_tab[i] = dis(gen);
        }

        //
        // PROCEDURE DE TEST SUR LES CODE NON-OPTIMISES
        //

        auto start_i_ref = std::chrono::system_clock::now();
        int r_nov = 0;
        for(int loop = 0; loop < nTest; loop += 1)
            r_nov = vec_max_index_x86_novect(a_tab, buffSize);
        auto stop_i_ref = std::chrono::system_clock::now();

        //
        // PROCEDURE DE TEST SUR LES CODE AUTO-OPTIMISES
        //

        auto start_i_x86 = std::chrono::system_clock::now();
        int r_x86 = 0;
        for(int loop = 0; loop < nTest; loop += 1)
            r_x86 = vec_max_index_x86(a_tab, buffSize);
        auto stop_i_x86 = std::chrono::system_clock::now();

        //
        // PROCEDURE DE TEST SUR LES CODES SSE4
        //

#ifdef __SSE4_2__
        auto start_i_sse4 = std::chrono::system_clock::now();
        int r_sse4 = 0;
        for(int loop = 0; loop < nTest; loop += 1)
            r_sse4 = vec_max_index_sse4(a_tab, buffSize);
        auto stop_i_sse4 = std::chrono::system_clock::now();
#endif

        //
        // PROCEDURE DE TEST SUR LES CODES AVX2
        //

#ifdef __AVX2__
        auto start_i_avx2 = std::chrono::system_clock::now();
        int r_avx2 = 0;
        for(int loop = 0; loop < nTest; loop += 1)
            r_avx2 = vec_max_index_avx2(a_tab, buffSize);
        auto stop_i_avx2 = std::chrono::system_clock::now();
#endif

        //
        // PROCEDURE DE TEST SUR LES CODES NEON
        //

#ifdef __ARM_NEON__
        auto start_i_neon = std::chrono::system_clock::now();
        int r_neon = 0;
        for(int loop = 0; loop < nTest; loop += 1)
            r_neon = vec_max_index_neon(a_tab, buffSize);
        auto stop_i_neon = std::chrono::system_clock::now();
#endif

        //
        // CALCUL DES TEMPS D'EXECUTION POUR LES STATISTIQUES
        //

        const int time_ref = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_ref - start_i_ref).count() / nTest;
        const int time_x86 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_x86 - start_i_x86).count() / nTest;
#ifdef __SSE4_2__
            const uint64_t time_sse4 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_sse4 - start_i_sse4).count() / nTest;
#endif
#ifdef __AVX2__
            const uint64_t time_avx2 = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_avx2 - start_i_avx2).count() / nTest;
#endif
#ifdef __ARM_NEON__
            const uint64_t time_neon = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_i_neon - start_i_neon).count() / nTest;
#endif

        //
        // On affiche les resultats de comparaison ainsi que les perfos temporelles
        //

        printf("    - [-x86-] unoptimized     \033[32mOK\033[0m [%5d ns]\n", (int)time_ref);

        if( r_nov == r_x86 ){
            printf("    - [AUTOV] auto-vectorized \033[32mOK\033[0m [%5d ns]\n", (int)time_x86);
        }else{
            printf("    - [AUTOV] auto-vectorized \033[31mKO\033[0m [%5d ns]\n", (int)time_x86);
            exit( EXIT_FAILURE );
        }

#ifdef __SSE4_2__
        if( r_nov == r_sse4 ){
            printf("    - [SSE-4] hand-written    \033[32mOK\033[0m [%5d ns]\n", (int)time_sse4);
        }else{
            printf("    - [SSE-4] hand-written    \033[31mKO\033[0m [%5d ns]\n", (int)time_sse4);
            exit( EXIT_FAILURE );
        }
#endif
#ifdef __AVX2__
        if( r_nov == r_avx2 ){
            printf("    - [AVX-2] hand-written    \033[32mOK\033[0m [%5d ns]\n", (int)time_avx2);
        }else{
            printf("    - [AVX-2] hand-written    \033[31mKO\033[0m [%5d ns]\n", (int)time_avx2);
            exit( EXIT_FAILURE );
        }
#endif
#ifdef __ARM_NEON__
        if( r_nov == r_neon ){
            printf("    - [-ARM-] hand-written    \033[32mOK\033[0m [%5d ns]\n", (int)time_neon);
        }else{
            printf("    - [-ARM-] hand-written    \033[31mKO\033[0m [%5d ns]\n", (int)time_neon);
            exit( EXIT_FAILURE );
        }
#endif
        printf("\n");
        
        delete[] a_tab;
}

    return EXIT_SUCCESS;
}
    
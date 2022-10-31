# SE301-High-Performance-Computing
 
## OpenMP experiments

### Stage 4 - Let's complexify a bit

It is not always possible to use OpenMP features without modifying the source code of the functions to be optimized. Indeed, the pragma available in the language allow to cover many use cases but not all :-)

To continue your training, you are now going to optimize a function that calculates the position of the maximum value present in an array of floating point numbers. The necessary environment for the performance evaluation is provided to you as before.

1 - Open the file that contains the calculation functions (src/vmax_index/ vec_max_index_x86.cpp) and complete the function vec_max_index_omp.

1 - Compile the program (vec_max_index_omp)

2 - Run the program from the terminal to check the functionality.

3 - Analyze the results.

4 - Call your teacher to discuss your implementation.


CAUTION:

Depending on how fast you are progressing in the teaching sequence, discuss with your teacher the interest of carrying out the next part (Stage-5). Switch either to (Stage 5 - std::threads) or go directly to part 3, SIMD programming.

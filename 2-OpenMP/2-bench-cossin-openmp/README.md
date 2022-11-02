# SE301-High-Performance-Computing
 
## OpenMP experiments

### Stage 2 - Let's try with a more complex example ;-)

In this part, we will make the computation function more complex in order to get a more realistic performance evaluation. Indeed, it is not very relevant to use OpenMP on kernels of very low complexity as you have noticed.

In this example we will be interested in the implementation of the following function:

C[i] = sqrt( cos(A[i]) ^ 2 + sin(B[i]) ^ 2 )


The necessary environment for the performance evaluation is provided as before. However, from now on you will start writing code!

1 - Open the file that contains the calculation functions (src/vcossin/vec_cossin_x86.hpp) and complete the vec_cossin_omp function.

1 - Compile the program (vec_cossin_omp)

2 - Run the program from the terminal.

3 - Analyze the results obtained and compare them to those obtained in step 1.

Once these tasks are done, go to the next part.

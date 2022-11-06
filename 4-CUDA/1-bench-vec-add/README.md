# SE301-High-Performance-Computing
 
## GPU experiments

### Stage 1 - The vector sum example like previously !

In this fourth part we are going to evaluate the interest of GPU graphic processors. The purpose of this first example is to allow you to take a step back on the use and interest of GPU devices.

This first pedagogical example that you know (too well?) by now and that realizes the sum of two vectors of N elements will allow you to observe the implementation of the SIMT programming model. To be able to program your GPU and access it, you will have to use the CUDA API developed by NVIDIA. The measured results will allow you to evaluate the gains in terms of execution time achievable with these circuits depending on the size of the data sets. 

1 - Open the file that contains the computational functions (**src/cuda/kernel/vec_add.cu**) and analyze it. Also take the time to analyze (**src/cuda/CUDAAdder.cu**) to understand how (1) the data is exchanged between the host CPU and the GPU and (2) the kernel executed.

1 - Compile the program (**main**) using a simple **Makefile**. To do this simply invoke the **make** command in the home directory.

2 - Run the program from the terminal by invoking the generated executable (**./bin/main**).

3 - Analyze the results obtained. Try to explain the results obtained in relation to the information you have been given in class.

4 - Explain what has changed in the compilation process compared to what you have done in steps **1-CPU**, **2-OpenMP** and **3-SIMD**.

Once this is done, move on to the next part 

# SE301-High-Performance-Computing
 
## GPU experiments

### Stage 3 – Harder, better, stronger

By teaching you so many pedagogical examples, you will think that programming in CUDA is simple... It's time to get rid of this feeling with the next example. This one is nothing else than our calculation of the maximum of an array. Indeed, in this processing the data are not independent. Normally you have been briefed by your teacher during his lecture. You can find the presentation used here :

https://developer.download.nvidia.com/assets/cuda/files/reduction.pdf

Contrary to the previous example you will have to complete the CUDAMax.cu class and implement the calculation kernel.

1 - Open the file which contains the calculation functions (**src/cuda/CUDAMax.cu**) and complete it.

2 - Open the file which contains the CUDA calculation kernel (**src/cuda/kernel/vec_max.cu**) and complete it. You can use / reuse parts of the source codes proposed by NVIDIA in its examples:

https://github.com/NVIDIA/cuda-samples/tree/master/Samples/2_Concepts_and_Techniques/reduction

Limit yourself to the examples **reduce1** or **reduce2**.

3 - Compile the program and run it.

4 - Run your program from the terminal and debug as much as necessary ;-).

5 - Analyze the results obtained.

When your work is finished, switch to the next section.


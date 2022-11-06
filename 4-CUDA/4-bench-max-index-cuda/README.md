# SE301-High-Performance-Computing
 
## GPU experiments

### Stage 4 – One more time

I will save you time. In this step you will adjust the code you developed earlier to calculate the position of the maximum instead of the maximum value. Be careful to always return the value of the first maximum in case of equality.

1 - Open the file that contains the calculation functions (src/cuda/CUDAMaxIndex.cu) and complete it (almost copy the class from the previous question).

2 - Open the file which contains the CUDA calculation kernel (src/cuda/kernel/vec_max_index.cu) and complete it. Here too, you can almost copy the answer of the previous question.

3 - Compile the program and run it.

4 - Run your program from the terminal and debug as much as necessary ;-).

5 - Analyze the obtained results and compare them.

If you haven't become a master of GPU programming you have understood the basic concepts. As you may have noticed, it is far from trivial to find the right parallelization approach and to adapt it to GPUs.

We'll say you have enough knowledge now to start accelerating the galaxy collision application. All you have to do is change your GitHub repository [LINK].

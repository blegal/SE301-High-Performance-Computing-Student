# SE301-High-Performance-Computing
 
## GPU experiments

### Stage 2 – Life is like a Sin curve

In this second example, you will write your first CUDA kernel. In order to highlight the computational capabilities of GPU type circuits, we are going to use the sine, cosine and sort functions that are complex. You are now going to reimplement the following calculation on CUDA:

**C[i] = sqrt( cos(A[i]) ^ 2 + cos(B[i]) ^ 2 )**

You will see, this is not complicated! Moreover, as this example is close to the previous one, you won't write much code. Indeed, we give you the CUDACosSin class.

1 - Open the file which contains the CUDA kernel (src/cuda/kernel/vec_cossin.cu), the cossin_arrays function and complete it.

1 - Compile the program (host + GPU)

2 - Run the program from the terminal to validate the behavior of your function.

3 - Analyze the results obtained. Compare these results with your OpenMP and SIMD solutions.

4 - In order to improve the performance of your solution, you can have a look here :

https://docs.nvidia.com/cuda/cuda-math-api/group__CUDA__MATH__INTRINSIC__SINGLE.html

Take the time to experiment with this new opportunity. Conclude on the interest of the approach and cite the 2 associated disadvantages.

Once these tasks are done, move on to the next part.


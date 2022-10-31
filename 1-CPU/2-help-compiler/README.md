# SE301-High-Performance-Computing
 
## CPU experiments

### Stage 2 - You can help the compiler!

In this second example we have deliberately chosen to set the optimization flag to **O2**. Your goal here is to help the compiler and indirectly your processor to improve the execution performance of your software code.

In this step you will try to optimize the ILP of the processor. Indeed, your processor which is at least a 6-way superscalar processor has several execution units that are massively unused in our context. This sub-optimality is due first to the data dependencies in the pipeline but also to the memory access time.

The structure of this example is similar to the previous example. You can verify this by looking at the software codes in the src/main.cpp file. Your work here consists of:

### Step 1

Compile and run the example provided to you by your teacher. Normally you should observe that the performance levels are equivalent. This is normal, it will be up to you to improve the description ;-)

### Step 2

Open the file src/vadd/additions.cpp. Modify the vec_add_unroll and vec_sum_unroll functions present. You have to manually unroll the loop core 8 times.

### Step 3

Compile and run your new version of the program. Observe the performance obtained after execution for the two new functions.

### Step 4

What are the reasons for these improvements?

Go to the next part.

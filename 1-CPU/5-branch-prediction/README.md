# SE301-High-Performance-Computing
 
## CPU experiments

### Stage 5 - Branch predictions, remove "if" from your codes!

The last thing you will observe is related to the internal architecture of the CPU. When executing a program, the CPU fetch-decode-execute-write pipeline is used. In order to obtain high levels of performance, it is important that the pipeline is used efficiently, minimizing the number of conditional branches. Indeed, despite the integration of branch predictors in current architectures, they can't do miracles...

In this example you have nothing to write. The pedagogical example to highlight these effects is available in the directory (src/vec_sum). Don't ask your teacher what these functions are for ;-) Once you have observed the software codes you know what you have to do:

1 - Compile the program (vec_sum_cond) and run it from the terminal.

2 - Analyze the results. Don't hesitate to have a look in the file (main.cpp) to understand the differences between the different tests.

3 - Try to modify the code to optimize the execution time of (function 2 - data set 2).

All this part has allowed you to increase your skills on the impact of algorithmic and/or software implementation on performance. Now it's time for you to move on. Take the direction of part 2 dedicated to the use of OpenMP.

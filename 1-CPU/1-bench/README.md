# SE301-High-Performance-Computing
 
## CPU experiments

### Stage 1 - The compiler, your friend!

The purpose of this first example is to show you the impact of the decisions made by the compiler on the efficiency of generated software codes. Indeed, if you use it correctly, the compiler allows you to exploit quite efficiently the basic or advanced features of your processor's architecture.

We will consider two basic calculation functions:

- The first one realizes the sum of 2 arrays of floating point data in a 3rd array.

- The second one calculates the sum of the data of the elements of an array containing floating point data.

You will find the source codes of these two calculation functions in the file [additions.cpp](./src/add/additions.cpp) located in the [./scr/add](./scr/add) directory.

To simplify your life, your teacher has kindly written the main function to measure the calculation time ([main.cpp](./src/main.cpp)) as well as the script to generate the program from the source files.

### Step 1:

Open the different files mentioned and analyze their content

### Step 2:

Open a terminal and go to the project directory

```
cd ~/SE301-High-Performance-Computing/1-CPU/1-bench
```

To generate the program we will have to create a temporary directory

```
mkdir build
cd build
```

Then generate the makefile containing the compilation commands

```
cmake3 ..
```

And finally compile the software codes

```
make
```

Now that all this is done we can run the program written in C++

```
./main
```

### Step 3:

What do you observe in your terminal? Are the measured data consistent with the course you were given?

### Step 4:

The compiler was configured to not optimize the code produced during the compilation process. We are going to tell it that it has to make some efforts. To do this we will modify the [CMakeLists.txt](./src/CMakeLists.txt) file.

Open the file CMakeLists.txt

Replace the flag **O0** present in the line by the flag **O1** :

```
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O0 -g0")
```

Recompile your program and restart the measurement of the execution time of the different functions.

Repeat the same sequence with the **O2**, **O3** and **Ofast** flags. For each experiment, note your observations concerning the execution times.

Try to analyze your observations from the information reported here:

[https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html](https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html)


Write a conclusion about the interest and impact of the compiler and the quality of your source codes on the performance of the programs!

Now that you have understood that the compiler is a nice tool to help you design efficient programs, we can move on...

Go to the next part.

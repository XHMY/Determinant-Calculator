# Determinant-Calculator
 Calculate determinant for n×n matrix using Laplace expansion with parallelization.

The matrix is in "data.in", it will be read line by line until filling the n*n matrix. The multi-thread feature is only for Unix/Linux operating system, if you are using Windows, you had better adapt it to suit individual needs.

All the code is in "determinant.cpp", "data.in" is a random matrix file input. "determinant.out" is the executable file in my Mac, which was compiled using -O2 and only for 10×10 matrix. (I need 0.3s to get the answer)

**This program is going to run slowly to get the answer for the big matrix, but it can notably speed up your fan.**


`g++ Determinant.cpp -O2 -std=c++11 -o Determinant.out`
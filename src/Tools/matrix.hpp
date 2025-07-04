#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

/*
* Transpose a matrix
* ------------------
* A: matrix to transpose
* T: transposed matrix
* n: number of rows of A
* m: number of columns of A
*/
// void transpose(int *A, int *T, int n, int m);
std::vector<int> transpose(const std::vector<int> &A, int n, int m);

void print_matrix(const std::vector<int> &A, int n, int m);

#endif
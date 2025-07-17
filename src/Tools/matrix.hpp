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
std::vector<char> transpose(const std::vector<char> &A, int n, int m);

void print_matrix(const std::vector<int> &A, int n, int m);

#endif
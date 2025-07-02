#include <vector>
#include <iostream>

/*
 * Transpose a matrix
 * ------------------
 * A: matrix to transpose
 * T: transposed matrix
 * n: number of rows of A
 * m: number of columns of A
 */

std::vector<int> transpose(std::vector<int> A, int n, int m){
    std::vector<int> T (n*m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            T[j * n + i] = A[i * m + j];
    return T;
}

void print_matrix(const std::vector<int> &A, int n, int m){
    for (int i = 0; i<n; i++){
        for (int j = 0; j < m; j++){
            std::cout << A[m*i + j] << " ";
        }
        std::cout << std::endl;
    }
}
#include <vector>
#include <iostream>

#ifdef USE_OPENMP
#include <omp.h>
#endif

/*
 * Transpose a matrix
 * ------------------
 * A: matrix to transpose
 * T: transposed matrix
 * n: number of rows of A
 * m: number of columns of A
 */

std::vector<char> transpose(const std::vector<char> &A, int n, int m)
{
    std::vector<char> T(n * m, 0);
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            T[j * n + i] = A[i * m + j];
    return T;
}

void print_matrix(const std::vector<int> &A, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cout << A[m * i + j] << " ";
        }
        std::cout << std::endl;
    }
}
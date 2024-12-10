#include <omp.h>
#include "../Tools/tools.h"

/*
 * Add Matrices
 * ------------
 * Adds two square matrices A and B of size n x n and stores the result in matrix C.
 * - A: a square matrix of size n x n
 * - B: a square matrix of size n x n
 * - C: a square matrix of size n x n
 * - n: the size of the matrices A, B, and C
 */
void add_square_matrices(int **A, int **B, int **C, int n, int deallocate)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    if (deallocate & 1) free_matrix(A, n);
    if (deallocate & 2) free_matrix(B, n);
}

/*
 * Subtract Matrices
 * -----------------
 * Subtracts two square matrices A and B of size n x n and stores the result in matrix C.
 * - A: a square matrix of size n x n
 * - B: a square matrix of size n x n
 * - C: a square matrix of size n x n
 * - n: the size of the matrices A, B, and C
 */
void subtract_square_matrices(int **A, int **B, int **C, int n, int deallocate)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    if (deallocate & 1) free_matrix(A, n);
    if (deallocate & 2) free_matrix(B, n);
}


int **add(int **A, int **B, int n, int deallocate)
{
    int **C = allocate_square_matrix(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    if (deallocate & 1)
        free_matrix(A, n);
    if (deallocate & 2)
        free_matrix(B, n);
    return C;
}

int **sub(int **A, int **B, int n, int deallocate)
{
    int **C = allocate_square_matrix(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    if (deallocate & 1)
        free_matrix(A, n);
    if (deallocate & 2)
        free_matrix(B, n);
    return C;
}

int **add_p(int **A, int **B, int n, int deallocate)
{
    int **C = allocate_square_matrix(n);
    int i, j;
    #pragma omp parallel for shared(A, B, C, n) private(i, j)
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    if (deallocate & 1)
        free_matrix(A, n);
    if (deallocate & 2)
        free_matrix(B, n);
    return C;
}

int **sub_p(int **A, int **B, int n, int deallocate)
{
    int **C = allocate_square_matrix(n);
    int i, j;
    #pragma omp parallel for shared(A, B, C, n) private(i, j)
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    if (deallocate & 1)
        free_matrix(A, n);
    if (deallocate & 2)
        free_matrix(B, n);
    return C;
}
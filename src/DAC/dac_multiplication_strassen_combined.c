#include <stdlib.h>
#include <stdio.h>
// #include <cblas.h>
#include <mkl.h>
#include <omp.h>
#include "../Tools/dac_tools.h"
#include "../Tools/tools.h"
#include "../Product/product.h"
#include "dac_multiplication_strassen_combined.h"

/*
 * Divide and Conquer Matrix Multiplication using Strassen's Algorithm
 * -------------------------------------------------------------------
 * This function takes two square matrices A and B of size n x n and returns
 * the product of the two matrices using the divide and conquer approach with
 * Strassen's Algorithm.
 * - A: a square matrix of size n x n
 * - B: a square matrix of size n x n
 * - n: the size of the matrices A and B
 *
 * returns:
 * - the product of the two matrices A and B
 *
 */
int **dac_square_mat_product_strassen_combined(int **A, int **B, int n, int deallocate, int threshold)
{
    if (n == threshold)
    {
        // int** C = square_mat_product_parra(A, B, threshold);
        double *A_double = malloc(n * n * sizeof(double));
        double *B_double = malloc( n * n * sizeof(double));
        double *C_double = malloc( n * n * sizeof(double));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A_double[i+j*n] = (double)A[i][j];
                B_double[i+j*n] = (double)B[i][j];
            }
        }   
        // openblas_set_num_threads(omp_get_max_threads());
        mkl_set_num_threads(omp_get_max_threads());

        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1.0, A_double, n, B_double, n, 0.0, C_double, n);
        int **C = allocate_square_matrix(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                C[i][j] = (int)C_double[i+j*n];
            }
        }

        free(A_double);
        free(B_double);
        free(C_double);

        if (deallocate & 1)
            free_matrix(A, n);
        if (deallocate & 2)
            free_matrix(B, n);
        return C;
    }
    else
    {
        int **C = allocate_square_matrix(n);
        int half_n = n / 2;
        int **A11 = allocate_square_matrix(half_n);
        int **A12 = allocate_square_matrix(half_n);
        int **A21 = allocate_square_matrix(half_n);
        int **A22 = allocate_square_matrix(half_n);
        int **B11 = allocate_square_matrix(half_n);
        int **B12 = allocate_square_matrix(half_n);
        int **B21 = allocate_square_matrix(half_n);
        int **B22 = allocate_square_matrix(half_n);

        // divide the matrices into submatrices
        int i, j;
        for (i = 0; i < half_n; i++)
        {
            for (j = 0; j < half_n; j++)
            {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + half_n];
                A21[i][j] = A[i + half_n][j];
                A22[i][j] = A[i + half_n][j + half_n];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + half_n];
                B21[i][j] = B[i + half_n][j];
                B22[i][j] = B[i + half_n][j + half_n];
            }
        }

        if (deallocate & 1)
            free_matrix(A, n);
        if (deallocate & 2)
            free_matrix(B, n);

        int** M1 = dac_square_mat_product_strassen_combined(add(A11, A22, half_n, 0), add(B11, B22, half_n, 0), half_n, 1 + 2, threshold);
        int** M2 = dac_square_mat_product_strassen_combined(add(A21, A22, half_n, 0), B11, half_n, 1, threshold);
        int** M3 = dac_square_mat_product_strassen_combined(A11, sub(B12, B22, half_n, 0), half_n, 2, threshold);
        int** M4 = dac_square_mat_product_strassen_combined(A22, sub(B21, B11, half_n, 0), half_n, 2, threshold);
        int** M5 = dac_square_mat_product_strassen_combined(add(A11, A12, half_n, 0), B22, half_n, 1, threshold);
        int** M6 = dac_square_mat_product_strassen_combined(sub(A21, A11, half_n, 1 + 2), add(B11, B12, half_n, 1 + 2), half_n, 1 + 2, threshold);
        int** M7 = dac_square_mat_product_strassen_combined(sub(A12, A22, half_n, 1 + 2), add(B21, B22, half_n, 1 + 2), half_n, 1 + 2, threshold);

        int **C11 = add(sub(add(M1, M4, half_n, 0), M5, half_n, 1), M7, half_n, 1 + 2);
        int **C12 = add(M3, M5, half_n, 2);
        int **C21 = add(M2, M4, half_n, 2);
        int **C22 = add(sub(add(M1, M3, half_n, 1 + 2), M2, half_n, 1 + 2), M6, half_n, 1 + 2);

        // combine the submatrices
        for (int i = 0; i < half_n; i++)
        {
            for (int j = 0; j < half_n; j++)
            {
                C[i][j] = C11[i][j];
                C[i][j + half_n] = C12[i][j];
                C[i + half_n][j] = C21[i][j];
                C[i + half_n][j + half_n] = C22[i][j];
            }
        }

        // deallocate the memory

        free_matrix(C11, half_n);
        free_matrix(C12, half_n);
        free_matrix(C21, half_n);
        free_matrix(C22, half_n);

        return C;
    }
}

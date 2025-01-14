#include <stdlib.h>
#include <omp.h>
#include "../Tools/dac_tools.h"
#include "../Tools/tools.h"
#include "../Product/product.h"


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
int **dac_square_mat_product_strassen_parra(int **A, int **B, int n, int deallocate)
{
    if (n == 4)
    { // base case
        // C[0][0] = A[0][0] * B[0][0];
        int **C = mat_4x4_product(A, B);
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
        int **M1;
        int **M2;
        int **M3;
        int **M4;
        int **M5;
        int **M6;
        int **M7;
        // int **C11;
        // int **C12;
        // int **C21;
        // int **C22;

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

        #pragma omp parallel sections 
        {
            #pragma omp section 
            {
                M1 = dac_square_mat_product_strassen_parra(add(A11, A22, half_n, 0), add(B11, B22, half_n, 0), half_n, 1 + 2);
            }
            #pragma omp section 
            {
                M2 = dac_square_mat_product_strassen_parra(add(A21, A22, half_n, 0), B11, half_n, 1);
            }
            #pragma omp section 
            {
                M3 = dac_square_mat_product_strassen_parra(A11, sub(B12, B22, half_n, 0), half_n, 2);
            }
            #pragma omp section 
            {
                M4 = dac_square_mat_product_strassen_parra(A22, sub(B21, B11, half_n, 0), half_n, 2);
            }
            #pragma omp section 
            {
                M5 = dac_square_mat_product_strassen_parra(add(A11, A12, half_n, 0), B22, half_n, 1);
            }
            #pragma omp section 
            {
                M6 = dac_square_mat_product_strassen_parra(sub(A21, A11, half_n, 0), add(B11, B12, half_n, 0), half_n, 1 + 2);
            }
            #pragma omp section 
            {
                M7 = dac_square_mat_product_strassen_parra(sub(A12, A22, half_n, 0), add(B21, B22, half_n, 0), half_n, 1 + 2);
            }
        }

        free_matrix(A11, half_n);
        free_matrix(A12, half_n);
        free_matrix(A21, half_n);
        free_matrix(A22, half_n);
        free_matrix(B11, half_n);
        free_matrix(B12, half_n);
        free_matrix(B21, half_n);
        free_matrix(B22, half_n);

        // #pragma omp parallel sections 
        // {
        //     #pragma omp section 
        //     {
        //         C11 = add(sub(add(M1, M4, half_n, 0), M5, half_n, 1), M7, half_n, 1);
        //     }
        //     #pragma omp section 
        //     {
        //         C12 = add(M3, M5, half_n, 0);
        //     }
        //     #pragma omp section 
        //     {
        //         C21 = add(M2, M4, half_n, 0);
        //     }
        //     #pragma omp section 
        //     {
        //         C22 = add(sub(add(M1, M3, half_n, 0), M2, half_n, 1), M6, half_n, 1);
        //     }
        // }

        int **C11 = add(sub(add(M1, M4, half_n, 0), M5, half_n, 1), M7, half_n, 1);
        int **C12 = add(M3, M5, half_n, 0);
        int **C21 = add(M2, M4, half_n, 0);
        int **C22 = add(sub(add(M1, M3, half_n, 0), M2, half_n, 1), M6, half_n, 1);

        free_matrix(M1, half_n);
        free_matrix(M2, half_n);
        free_matrix(M3, half_n);
        free_matrix(M4, half_n);
        free_matrix(M5, half_n);
        free_matrix(M6, half_n);
        free_matrix(M7, half_n);

        // combine the submatrices
        int i2, j2;
        // #pragma omp parallel for private(i2, j2) shared(C, half_n, C11, C12, C21, C22)
        for (i2 = 0; i2 < half_n; i2++)
        {
            for (j2 = 0; j2 < half_n; j2++)
            {
                C[i2][j2] = C11[i2][j2];
                C[i2][j2 + half_n] = C12[i2][j2];
                C[i2 + half_n][j2] = C21[i2][j2];
                C[i2 + half_n][j2 + half_n] = C22[i2][j2];
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

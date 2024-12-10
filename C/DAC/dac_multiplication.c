#include <stdlib.h>
#include "../Tools/dac_tools.h"
#include "../Tools/tools.h"
#include "../Product/product.h"

/*
 * Divide and Conquer Matrix Multiplication
 * ----------------------------------------
 * This function takes two square matrices A and B of size n x n and returns
 * the product of the two matrices using the divide and conquer approach.
 * - A: a square matrix of size n x n
 * - B: a square matrix of size n x n
 * - n: the size of the matrices A and B
 *
 * returns:
 * - the product of the two matrices A and B
 *
 */
int **dac_square_mat_product(int **A, int **B, int n)
{
    if (n == 4)
    { // base case
        // C[0][0] = A[0][0] * B[0][0];
        int **C = mat_4x4_product(A, B);
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

        // compute the product of the submatrices
        int** C11 = add(dac_square_mat_product(A11, B11, half_n), dac_square_mat_product(A12, B21, half_n), half_n, 1+2);
        int** C12 = add(dac_square_mat_product(A11, B12, half_n), dac_square_mat_product(A12, B22, half_n), half_n, 1+2);
        int** C21 = add(dac_square_mat_product(A21, B11, half_n), dac_square_mat_product(A22, B21, half_n), half_n, 1+2);
        int** C22 = add(dac_square_mat_product(A21, B12, half_n), dac_square_mat_product(A22, B22, half_n), half_n, 1+2);

        // combine the submatrices
        for (i = 0; i < half_n; i++)
        {
            for (j = 0; j < half_n; j++)
            {
                C[i][j] = C11[i][j];
                C[i][j + half_n] = C12[i][j];
                C[i + half_n][j] = C21[i][j];
                C[i + half_n][j + half_n] = C22[i][j];
            }
        }

        // deallocate the memory
        free_matrix(A11, half_n);
        free_matrix(A12, half_n);
        free_matrix(A21, half_n);
        free_matrix(A22, half_n);
        free_matrix(B11, half_n);
        free_matrix(B12, half_n);
        free_matrix(B21, half_n);
        free_matrix(B22, half_n);
        free_matrix(C11, half_n);
        free_matrix(C12, half_n);
        free_matrix(C21, half_n);
        free_matrix(C22, half_n);
        return C;
    }

}

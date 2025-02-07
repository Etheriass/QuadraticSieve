#include <stdio.h>
#include <stdlib.h>
#include "tools.hpp"

/*
 * Transpose a matrix
 * ------------------
 * A: matrix to transpose
 * T: transposed matrix
 * n: number of rows of A
 * m: number of columns of A
 */
void transpose(int *A, int *T, int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            T[j * n + i] = A[i * m + j];
}

/*
 * Print a matrix
 * --------------
 * A: matrix to print
 * n: number of rows of A
 * m: number of columns of A
 */
void printMatrix(int **A, int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("[");
        for (j = 0; j < m; j++)
        {
            printf("%d", A[i][j]);
            if (j < m - 1)
                printf(" ");
        }
        printf("]\n");
    }
}

/*
 * Print square a matrix
 * --------------
 * A: matrix to print
 * n: number of rows and columns of A
 */
// void print_square_matrix(int **A, int n) {
//     int i, j;
//     for (i = 0; i < n; i++) {
//         printf("[");
//         for (j = 0; j < n; j++) {
//             printf("%d", A[i][j]);
//             if (j < n - 1)
//                 printf(", ");
//         }
//         printf("]\n");
//     }
// }

void print_square_matrix(int **A, int n)
{
    int min, max, w = 0, n1, n2, nw;
    min = max = A[0][0];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (min > A[i][j])
                min = A[i][j];
            if (max < A[i][j])
                max = A[i][j];
        }
    }
    n1 = snprintf(NULL, 0, "%d", min);
    n2 = snprintf(NULL, 0, "%d", max);
    nw = n1 > n2 ? n1 : n2;

    for (int i = 0; i < n; i++)
    {
        printf("[");
        for (int j = 0; j < n; j++)
        {
            printf(" %*d", nw, A[i][j]);
        }
        printf("]\n");
    }
    fflush(stdout);
}

/*
 * Allocate Matrix
 * ---------------
 * Allocates memory for a 2D matrix of size rows x cols.
 * - rows: the number of rows in the matrix
 * - cols: the number of columns in the matrix
 */
int **allocate_matrix(int rows, int cols)
{
    int **M = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        M[i] = (int *)malloc(cols * sizeof(int));
    }
    return M;
}

/*
 * Allocate square Matrix
 * ----------------------
 * Allocates memory for a 2D square matrix of size n.
 * - M: a pointer to a pointer to an integer matrix
 * - n: the number of rows and columns in the matrix
 * returns:
 * - the allocated square matrix
 */
int **allocate_square_matrix(int n)
{
    int **M = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        M[i] = (int *)malloc(n * sizeof(int));
    }
    return M;
}

/*
 * Free Matrix
 * -----------
 * Frees the memory allocated for a 2D matrix.
 * - M: a pointer to an integer matrix
 * - rows: the number of rows in the matrix
 */
void free_matrix(int **M, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free(M[i]);
    }
    free(M);
}

/*
 * Is Matrix Equal
 * ---------------
 * Check if two matrices are equal.
 * - A: a square matrix of size n x n
 * - B: a square matrix of size n x n
 * returns:
 * - 1 if the matrices are equal, 0 otherwise
 */

int is_matrix_equal(int **A, int **B, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (A[i][j] != B[i][j])
                return 0;
    return 1;
}

/*
 * Is Matrix Equal in Z2
 * ---------------------
 * Check if two matrices are equal in Z/2Z.
 * - A: a square matrix of size n x n
 * - B: a square matrix of size n x n
 * returns:
 * - 1 if the matrices are equal, 0 otherwise
 */

int is_matrix_equal_in_Z2(int **A, int **B, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (A[i][j]%2 != B[i][j]%2)
                return 0;
    return 1;
}
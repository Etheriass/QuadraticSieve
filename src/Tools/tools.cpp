#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "tools.hpp"

int sum_vec(const std::vector<int> &u){
    int sum = 0;
    for (const int val: u)
        sum += val;
    return sum;
}

/*
 * Transpose a matrix
 * ------------------
 * A: matrix to transpose
 * T: transposed matrix
 * n: number of rows of A
 * m: number of columns of A
 */
// void transpose(int *A, int *T, int n, int m)
// {
//     int i, j;
//     for (i = 0; i < n; i++)
//         for (j = 0; j < m; j++)
//             T[j * n + i] = A[i * m + j];
// }

std::vector<int> transpose(std::vector<int> A, int n, int m){
    std::vector<int> T (n*m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            T[j * n + i] = A[i * m + j];
    return T;
}

void printColVec(const std::vector<int>& u){ // pass the vector by const reference to avoid unnecessary copying
    for (const int element: u){
        std::cout << element << std::endl;
    }
}

void printRowVec(const std::vector<int>& u){
    std::cout << "[";
    for (const int element: u){
        std::cout << element << " ";
    }
    std::cout << "]" << std::endl;
}

void printMatrix(const std::vector<int> &A, int n, int m){
    for (int i = 0; i<n; i++){
        for (int j = 0; j < m; j++){
            std::cout << A[m*i + j] << " ";
        }
        std::cout << std::endl;
    }
}

/*
 * Print a matrix
 * --------------
 * A: matrix to print
 * n: number of rows of A
 * m: number of columns of A
 */
void printArrayMatrix(int **A, int n, int m)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("[");
        for (j = 0; j < m; j++){
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
void print_square_matrix(int **A, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        printf("[");
        for (j = 0; j < n; j++) {
            printf("%d", A[i][j]);
            if (j < n - 1)
                printf(", ");
        }
        printf("]\n");
    }
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
int **allocate_square_matrix(int n, int value)
{
    int **M = (int **)malloc(n * sizeof(int *));
    if (!value){
        for (int i = 0; i < n; i++){
            M[i] = (int *)malloc(n * sizeof(int));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            M[i] = (int*)malloc(n * sizeof(int));
            for (int j = 0; j < n; ++j) {
                M[i][j] = value;
            }
        }
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
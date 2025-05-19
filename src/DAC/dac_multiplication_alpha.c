#include <stdlib.h>
#include <stdio.h>
// #include <cblas.h>
#include <mkl.h>
#include <omp.h>
#include "../Tools/dac_tools.h"
#include "../Tools/tools.h"
#include "../Product/product.h"

/*
 * Divide and Conquer Matrix Multiplication using Alpha Tensor's Algorithm
 * -------------------------------------------------------------------
 * This function takes two square matrices A and B of size n x n and returns
 * the product of the two matrices using the divide and conquer approach with
 * Alpha Tensor's Algorithm.
 * - A: a square matrix of size n x n
 * - B: a square matrix of size n x n
 * - n: the size of the matrices A and B
 *
 * returns:
 * - the product of the two matrices A and B
 *
 */
int **dac_square_mat_product_alpha(int **A, int **B, int n, int deallocate, int threshold)
{
    if (n == threshold)
    {
        // int** C = square_mat_product_parra(A, B, threshold);
        double *A_double = malloc(n * n * sizeof(double));
        double *B_double = malloc(n * n * sizeof(double));
        double *C_double = malloc(n * n * sizeof(double));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A_double[i + j * n] = (double)A[i][j];
                B_double[i + j * n] = (double)B[i][j];
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
                C[i][j] = (int)C_double[i + j * n];
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
        int quarter_n = n / 4;
        int **A11 = allocate_square_matrix(quarter_n);
        int **A12 = allocate_square_matrix(quarter_n);
        int **A13 = allocate_square_matrix(quarter_n);
        int **A14 = allocate_square_matrix(quarter_n);
        int **A21 = allocate_square_matrix(quarter_n);
        int **A22 = allocate_square_matrix(quarter_n);
        int **A23 = allocate_square_matrix(quarter_n);
        int **A24 = allocate_square_matrix(quarter_n);
        int **A31 = allocate_square_matrix(quarter_n);
        int **A32 = allocate_square_matrix(quarter_n);
        int **A33 = allocate_square_matrix(quarter_n);
        int **A34 = allocate_square_matrix(quarter_n);
        int **A41 = allocate_square_matrix(quarter_n);
        int **A42 = allocate_square_matrix(quarter_n);
        int **A43 = allocate_square_matrix(quarter_n);
        int **A44 = allocate_square_matrix(quarter_n);
        int **B11 = allocate_square_matrix(quarter_n);
        int **B12 = allocate_square_matrix(quarter_n);
        int **B13 = allocate_square_matrix(quarter_n);
        int **B14 = allocate_square_matrix(quarter_n);
        int **B21 = allocate_square_matrix(quarter_n);
        int **B22 = allocate_square_matrix(quarter_n);
        int **B23 = allocate_square_matrix(quarter_n);
        int **B24 = allocate_square_matrix(quarter_n);
        int **B31 = allocate_square_matrix(quarter_n);
        int **B32 = allocate_square_matrix(quarter_n);
        int **B33 = allocate_square_matrix(quarter_n);
        int **B34 = allocate_square_matrix(quarter_n);
        int **B41 = allocate_square_matrix(quarter_n);
        int **B42 = allocate_square_matrix(quarter_n);
        int **B43 = allocate_square_matrix(quarter_n);
        int **B44 = allocate_square_matrix(quarter_n);

        // divide the matrices into submatrices
        for (int i = 0; i < quarter_n; i++)
        {
            for (int j = 0; j < quarter_n; j++)
            {
                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + quarter_n];
                A13[i][j] = A[i][j + 2 * quarter_n];
                A14[i][j] = A[i][j + 3 * quarter_n];
                A21[i][j] = A[i + quarter_n][j];
                A22[i][j] = A[i + quarter_n][j + quarter_n];
                A23[i][j] = A[i + quarter_n][j + 2 * quarter_n];
                A24[i][j] = A[i + quarter_n][j + 3 * quarter_n];
                A31[i][j] = A[i + 2 * quarter_n][j];
                A32[i][j] = A[i + 2 * quarter_n][j + quarter_n];
                A33[i][j] = A[i + 2 * quarter_n][j + 2 * quarter_n];
                A34[i][j] = A[i + 2 * quarter_n][j + 3 * quarter_n];
                A41[i][j] = A[i + 3 * quarter_n][j];
                A42[i][j] = A[i + 3 * quarter_n][j + quarter_n];
                A43[i][j] = A[i + 3 * quarter_n][j + 2 * quarter_n];
                A44[i][j] = A[i + 3 * quarter_n][j + 3 * quarter_n];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + quarter_n];
                B13[i][j] = B[i][j + 2 * quarter_n];
                B14[i][j] = B[i][j + 3 * quarter_n];
                B21[i][j] = B[i + quarter_n][j];
                B22[i][j] = B[i + quarter_n][j + quarter_n];
                B23[i][j] = B[i + quarter_n][j + 2 * quarter_n];
                B24[i][j] = B[i + quarter_n][j + 3 * quarter_n];
                B31[i][j] = B[i + 2 * quarter_n][j];
                B32[i][j] = B[i + 2 * quarter_n][j + quarter_n];
                B33[i][j] = B[i + 2 * quarter_n][j + 2 * quarter_n];
                B34[i][j] = B[i + 2 * quarter_n][j + 3 * quarter_n];
                B41[i][j] = B[i + 3 * quarter_n][j];
                B42[i][j] = B[i + 3 * quarter_n][j + quarter_n];
                B43[i][j] = B[i + 3 * quarter_n][j + 2 * quarter_n];
                B44[i][j] = B[i + 3 * quarter_n][j + 3 * quarter_n];
            }
        }

        if (deallocate & 1)
            free_matrix(A, n);
        if (deallocate & 2)
            free_matrix(B, n);

        int ***h = (int ***)malloc(47 * sizeof(int **));
        // for (int i = 0; i < 47; i++)
        // {
        //     h[i] = allocate_square_matrix(quarter_n);
        //     if (h[i] == NULL) {
        //         fprintf(stderr, "Memory allocation failed\n");
        //         exit(EXIT_FAILURE);
        //     }
        // }
        if (h == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        h[0] = dac_square_mat_product_alpha(A11, B13, quarter_n, 0, threshold);
        h[1] = dac_square_mat_product_alpha(add(A11, add(A31, A33, quarter_n, 0), quarter_n, 2), add(B11, add(B31, B33, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[2] = dac_square_mat_product_alpha(add(A11, add(A31, A34, quarter_n, 0), quarter_n, 2), add(B12, add(B42, B43, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[3] = dac_square_mat_product_alpha(add(A13, add(A21, A23, quarter_n, 0), quarter_n, 2), add(B13, add(B14, B34, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[4] = dac_square_mat_product_alpha(add(A11, A31, quarter_n, 0), add(B11, add(B12, add(B13, add(B31, add(B33, add(B42, B43, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[5] = dac_square_mat_product_alpha(add(A13, A23, quarter_n, 0), add(B13, add(B14, add(B32, add(B33, add(B34, add(B42, B43, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[6] = dac_square_mat_product_alpha(add(A14, add(A43, A44, quarter_n, 0), quarter_n, 2), add(B31, add(B33, B42, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[7] = dac_square_mat_product_alpha(add(A14, add(A41, A44, quarter_n, 0), quarter_n, 2), add(B13, add(B14, B44, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[8] = dac_square_mat_product_alpha(add(A13, add(A23, A24, quarter_n, 0), quarter_n, 2), add(B32, add(B42, B43, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[9] = dac_square_mat_product_alpha(add(A14, A44, quarter_n, 0), add(B13, add(B14, add(B32, add(B33, add(B41, add(B43, B44, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[10] = dac_square_mat_product_alpha(A33, add(B11, add(B22, add(B23, add(B31, B32, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2, threshold);
        h[11] = dac_square_mat_product_alpha(add(A12, add(A32, A33, quarter_n, 0), quarter_n, 2), add(B22, add(B23, B32, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[12] = dac_square_mat_product_alpha(A34, add(B12, add(B21, add(B23, add(B41, B42, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2, threshold);
        h[13] = dac_square_mat_product_alpha(add(A12, A32, quarter_n, 0), add(B21, add(B22, add(B23, add(B32, B41, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[14] = dac_square_mat_product_alpha(add(A12, add(A32, A34, quarter_n, 0), quarter_n, 2), add(B21, add(B23, B41, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[15] = dac_square_mat_product_alpha(A21, add(B12, add(B14, add(B22, add(B23, B34, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2, threshold);
        h[16] = dac_square_mat_product_alpha(add(A12, add(A21, A22, quarter_n, 0), quarter_n, 2), add(B12, add(B22, B23, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[17] = dac_square_mat_product_alpha(add(A12, A22, quarter_n, 0), add(B12, add(B22, add(B23, add(B24, B44, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[18] = dac_square_mat_product_alpha(A24, add(B23, add(B24, add(B32, add(B42, B44, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2, threshold);
        h[19] = dac_square_mat_product_alpha(add(A12, add(A23, add(A24, add(A31, A33, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), B32, quarter_n, 1, threshold);
        h[20] = dac_square_mat_product_alpha(add(A12, add(A22, A24, quarter_n, 0), quarter_n, 2), add(B23, add(B24, B44, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[21] = dac_square_mat_product_alpha(A43, add(B23, add(B24, add(B31, add(B34, B41, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2, threshold);
        h[22] = dac_square_mat_product_alpha(add(A11, add(A13, add(A14, add(A23, add(A24, add(A31, A34, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), add(B42, B43, quarter_n, 0), quarter_n, 1 + 2, threshold);
        h[23] = dac_square_mat_product_alpha(add(A12, add(A42, A43, quarter_n, 0), quarter_n, 2), add(B23, add(B24, B34, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[24] = dac_square_mat_product_alpha(add(A12, A42, quarter_n, 0), add(B11, add(B21, add(B23, add(B24, B34, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[25] = dac_square_mat_product_alpha(add(A12, add(A42, A42, quarter_n, 0), quarter_n, 2), add(B11, add(B21, B23, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[26] = dac_square_mat_product_alpha(A14, B43, quarter_n, 0, threshold);
        h[27] = dac_square_mat_product_alpha(add(A12, add(A21, add(A22, add(A31, A34, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), B12, quarter_n, 1, threshold);
        h[28] = dac_square_mat_product_alpha(add(A12, add(A21, add(A23, add(A42, A43, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), B34, quarter_n, 1, threshold);
        h[29] = dac_square_mat_product_alpha(add(A12, add(A31, add(A33, add(A41, A42, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), B11, quarter_n, 1, threshold);
        h[30] = dac_square_mat_product_alpha(A41, add(B11, add(B14, add(B21, add(B23, B44, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2, threshold);
        h[31] = dac_square_mat_product_alpha(add(A12, add(A32, add(A34, add(A43, A44, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), B41, quarter_n, 1, threshold);
        h[32] = dac_square_mat_product_alpha(add(A12, add(A22, add(A24, add(A41, A44, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), B44, quarter_n, 1, threshold);
        h[33] = dac_square_mat_product_alpha(add(A21, add(A31, A41, quarter_n, 0), quarter_n, 2), add(B11, add(B12, B14, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[34] = dac_square_mat_product_alpha(add(A12, add(A21, add(A22, add(A32, A33, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), add(B22, B23, quarter_n, 0), quarter_n, 1 + 2, threshold);
        h[35] = dac_square_mat_product_alpha(add(A12, add(A24, add(A32, A43, quarter_n, 0), quarter_n, 2), quarter_n, 2), add(B23, add(B24, add(B32, B41, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[36] = dac_square_mat_product_alpha(add(A12, add(A21, add(A33, A42, quarter_n, 0), quarter_n, 2), quarter_n, 2), add(B11, add(B22, add(B23, B34, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[37] = dac_square_mat_product_alpha(add(A22, add(A32, A42, quarter_n, 0), quarter_n, 2), add(B21, add(B22, B24, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[38] = dac_square_mat_product_alpha(A13, B23, quarter_n, 0, threshold);
        h[39] = dac_square_mat_product_alpha(A13, B33, quarter_n, 0, threshold);
        h[40] = dac_square_mat_product_alpha(add(A11, add(A13, add(A14, add(A21, add(A23, add(A41, A44, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), add(B13, B14, quarter_n, 0), quarter_n, 1 + 2, threshold);
        h[41] = dac_square_mat_product_alpha(add(A12, add(A32, add(A34, add(A41, A42, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), add(B21, B23, quarter_n, 0), quarter_n, 1 + 2, threshold);
        h[42] = dac_square_mat_product_alpha(add(A24, add(A34, A44, quarter_n, 0), quarter_n, 2), add(B41, add(B42, B44, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[43] = dac_square_mat_product_alpha(add(A23, add(A33, A43, quarter_n, 0), quarter_n, 2), add(B31, add(B32, B34, quarter_n, 0), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[44] = dac_square_mat_product_alpha(add(A11, add(A13, add(A14, add(A31, add(A33, add(A43, A44, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), add(B31, B33, quarter_n, 0), quarter_n, 1 + 2, threshold);
        h[45] = dac_square_mat_product_alpha(add(A12, add(A22, add(A34, A41, quarter_n, 0), quarter_n, 2), quarter_n, 2), add(B12, add(B21, add(B23, B44, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 1 + 2, threshold);
        h[46] = dac_square_mat_product_alpha(add(A12, add(A22, add(A24, add(A42, A43, quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), add(B23, B24, quarter_n, 0), quarter_n, 1 + 2, threshold);

        // deallocate the memory
        free_matrix(A11, quarter_n);
        free_matrix(A12, quarter_n);
        free_matrix(A13, quarter_n);
        free_matrix(A14, quarter_n);
        free_matrix(A21, quarter_n);
        free_matrix(A22, quarter_n);
        free_matrix(A23, quarter_n);
        free_matrix(A24, quarter_n);
        free_matrix(A31, quarter_n);
        free_matrix(A32, quarter_n);
        free_matrix(A33, quarter_n);
        free_matrix(A34, quarter_n);
        free_matrix(A41, quarter_n);
        free_matrix(A42, quarter_n);
        free_matrix(A43, quarter_n);
        free_matrix(A44, quarter_n);
        free_matrix(B11, quarter_n);
        free_matrix(B12, quarter_n);
        free_matrix(B13, quarter_n);
        free_matrix(B14, quarter_n);
        free_matrix(B21, quarter_n);
        free_matrix(B22, quarter_n);
        free_matrix(B23, quarter_n);
        free_matrix(B24, quarter_n);
        free_matrix(B31, quarter_n);
        free_matrix(B32, quarter_n);
        free_matrix(B33, quarter_n);
        free_matrix(B34, quarter_n);
        free_matrix(B41, quarter_n);
        free_matrix(B42, quarter_n);
        free_matrix(B43, quarter_n);
        free_matrix(B44, quarter_n);

        int **C11 = add(h[14], add(h[25], add(h[1], add(h[29], add(h[31], add(h[38], add(h[39], add(h[41], add(h[44], h[6], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);
        int **C21 = add(h[10], add(h[11], add(h[13], add(h[19], add(h[21], add(h[23], add(h[24], add(h[28], add(h[34], add(h[35], add(h[36], add(h[37], add(h[43], h[46], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);
        int **C31 = add(h[10], add(h[11], add(h[13], add(h[14], add(h[25], add(h[29], add(h[38], h[41], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);
        int **C41 = add(h[14], add(h[21], add(h[23], add(h[24], add(h[25], add(h[31], add(h[38], h[41], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);

        int **C12 = add(h[11], add(h[16], add(h[19], add(h[22], add(h[26], add(h[27], add(h[34], add(h[38], add(h[2], h[8], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);
        int **C22 = add(h[11], add(h[16], add(h[17], add(h[18], add(h[19], add(h[20], add(h[34], h[38], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);
        int **C32 = add(h[11], add(h[12], add(h[13], add(h[14], add(h[16], add(h[27], add(h[34], h[38], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);
        int **C42 = add(h[12], add(h[13], add(h[14], add(h[17], add(h[18], add(h[20], add(h[31], add(h[32], add(h[35], add(h[37], add(h[41], add(h[42], add(h[45], h[46], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);

        int **C13 = add(h[0], add(h[26], add(h[38], h[39], quarter_n, 0), quarter_n, 2), quarter_n, 2);
        int **C23 = add(h[15], add(h[16], add(h[17], add(h[18], add(h[20], add(h[38], add(h[39], add(h[3], add(h[5], h[8], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);
        int **C33 = add(h[10], add(h[11], add(h[12], add(h[13], add(h[14], add(h[0], add(h[1], add(h[38], add(h[2], h[4], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);
        int **C43 = add(h[9], add(h[21], add(h[23], add(h[24], add(h[25], add(h[26], add(h[30], add(h[38], add(h[6], h[7], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);

        int **C14 = add(h[0], add(h[20], add(h[23], add(h[28], add(h[32], add(h[38], add(h[40], add(h[46], add(h[3], h[7], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);
        int **C24 = add(h[15], add(h[16], add(h[17], add(h[20], add(h[23], add(h[28], add(h[38], h[46], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);
        int **C34 = add(h[15], add(h[16], add(h[17], add(h[24], add(h[25], add(h[27], add(h[29], add(h[30], add(h[33], add(h[34], add(h[36], add(h[37], add(h[41], h[45], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);
        int **C44 = add(h[20], add(h[23], add(h[24], add(h[25], add(h[30], add(h[32], add(h[38], h[46], quarter_n, 0), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2), quarter_n, 2);

        // deallocate the memory
        for (int i = 0; i < 47; i++)
        {
            free_matrix(h[i], quarter_n);
        }
        free(h);

        // combine the submatrices
        for (int i = 0; i < quarter_n; i++)
        {
            for (int j = 0; j < quarter_n; j++)
            {
                C[i][j] = C11[i][j];
                C[i][j + quarter_n] = C12[i][j];
                C[i][j + 2 * quarter_n] = C13[i][j];
                C[i][j + 3 * quarter_n] = C14[i][j];
                C[i + quarter_n][j] = C21[i][j];
                C[i + quarter_n][j + quarter_n] = C22[i][j];
                C[i + quarter_n][j + 2 * quarter_n] = C23[i][j];
                C[i + quarter_n][j + 3 * quarter_n] = C24[i][j];
                C[i + 2 * quarter_n][j] = C31[i][j];
                C[i + 2 * quarter_n][j + quarter_n] = C32[i][j];
                C[i + 2 * quarter_n][j + 2 * quarter_n] = C33[i][j];
                C[i + 2 * quarter_n][j + 3 * quarter_n] = C34[i][j];
                C[i + 3 * quarter_n][j] = C41[i][j];
                C[i + 3 * quarter_n][j + quarter_n] = C42[i][j];
                C[i + 3 * quarter_n][j + 2 * quarter_n] = C43[i][j];
                C[i + 3 * quarter_n][j + 3 * quarter_n] = C44[i][j];
            }
        }

        // deallocate the memory
        free_matrix(C11, quarter_n);
        free_matrix(C12, quarter_n);
        free_matrix(C13, quarter_n);
        free_matrix(C14, quarter_n);
        free_matrix(C21, quarter_n);
        free_matrix(C22, quarter_n);
        free_matrix(C23, quarter_n);
        free_matrix(C24, quarter_n);
        free_matrix(C31, quarter_n);
        free_matrix(C32, quarter_n);
        free_matrix(C33, quarter_n);
        free_matrix(C34, quarter_n);
        free_matrix(C41, quarter_n);
        free_matrix(C42, quarter_n);
        free_matrix(C43, quarter_n);
        free_matrix(C44, quarter_n);

        return C;
    }
}

// h[0] = A11 * B13;
// h[1] = (A11 + A31 + A33) * (B11 + B31 + B33);
// h[2] = (A11 + A31 + A34) * (B12 + B42 + B43);
// h[3] = (A13 + A21 + A23) * (B13 + B14 + B34);
// h[4] = (A11 + A31) * (B11 + B12 + B13 + B31 + B33 + B42 + B43);
// h[5] = (A13 + A23) * (B13 + B14 + B32 + B33 + B34 + B42 + B43);
// h[6] = (A14 + A43 + A44) * (B31 + B33 + B42);
// h[7] = (A14 + A41 + A44) * (B13 + B14 + B44);
// h[8] = (A13 + A23 + A24) * (B32 + B42 + B43);
// h[9] = (A14 + A44) * (B13 + B14 + B32 + B33 + B41 + B43 + B44);
// h[10] = A33 * (B11 + B22 + B23 + B31 + B32);
// h[11] = (A12 + A32 + A33) * (B22 + B23 + B32);
// h[12] = A34 * (B12 + B21 + B23 + B41 + B42);
// h[13] = (A12 + A32) * (B21 + B22 + B23 + B32 + B41);
// h[14] = (A12 + A32 + A34) * (B21 + B23 + B41);
// h[15] = A21 * (B12 + B14 + B22 + B23 + B34);
// h[16] = (A12 + A21 + A22) * (B12 + B22 + B23);
// h[17] = (A12 + A22) * (B12 + B22 + B23 + B24 + B44);
// h[18] = A24 * (B23 + B24 + B32 + B42 + B44);
// h[19] = (A12 + A23 + A24 + A31 + A33) * B32;
// h[20] = (A12 + A22 + A24) * (B23 + B24 + B44);
// h[21] = A43 * (B23 + B24 + B31 + B34 + B41);
// h[22] = (A11 + A13 + A14 + A23 + A24 + A31 + A34) * (B42 + B43);
// h[23] = (A12 + A42 + A43) * (B23 + B24 + B34);
// h[24] = (A12 + A42) * (B11 + B21 + B23 + B24 + B34);
// h[25] = (A12 + A42 + A42) * (B11 + B21 + B23);
// h[26] = A14 * B43;
// h[27] = (A12 + A21 + A22 + A31 + A34) * B12;
// h[28] = (A12 + A21 + A23 + A42 + A43) * B34;
// h[29] = (A12 + A31 + A33 + A41 + A42) * B11;
// h[30] = A41 * (B11 + B14 + B21 + B23 + B44);
// h[31] = (A12 + A32 + A34 + A43 + A44) * B41;
// h[32] = (A12 + A22 + A24 + A41 + A44) * B44;
// h[33] = (A21 + A31 + A41) * (B11 + B12 + B14);
// h[34] = (A12 + A21 + A22 + A32 + A33) * (B22 + B23);
// h[35] = (A12 + A24 + A32 + A43) * (B23 + B24 + B32 + B41);
// h[36] = (A12 + A21 + A33 + A42) * (B11 + B22 + B23 + B34);
// h[37] = (A22 + A32 + A42) * (B21 + B22 + B24);
// h[38] = A13 * B23;
// h[39] = A13 * B33;
// h[40] = (A11 + A13 + A14 + A21 + A23 + A41 + A44) * (B13 + B14);
// h[41] = (A12 + A32 + A34 + A41 + A42) * (B21 + B23);
// h[42] = (A24 + A34 + A44) * (B41 + B42 + B44);
// h[43] = (A23 + A33 + A43) * (B31 + B32 + B34);
// h[44] = (A11 + A13 + A14 + A31 + A33 + A43 + A44) * (B31 + B33);
// h[45] = (A12 + A22 + A34 + A41) * (B12 + B21 + B23 + B44);
// h[46] = (A12 + A22 + A24 + A42 + A43) * (B23 + B24);
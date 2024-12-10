#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <cblas.h>
#include "../Tools/tools.h"
#include "../Tools/dac_tools.h"
#include "../DAC/dac_multiplication.h"
#include "../DAC/dac_multiplication_parra.h"
#include "../DAC/dac_multiplication_strassen.h"
#include "../DAC/dac_multiplication_strassen_parra.h"
#include "../DAC/dac_multiplication_strassen_combined.h"
#include "../DAC/dac_multiplication_alpha.h"
#include "../Product/product.h"

int main()
{
    int n = 4096;
    int print = 0;
    int **A = allocate_square_matrix(n);
    int **B = allocate_square_matrix(n);

    double *A_double = malloc(n*n * sizeof(double));
    double *B_double = malloc(n*n * sizeof(double));
    double *C_double = malloc(n* n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = 1;
            B[i][j] = 1;
            A_double[i+j*n] = 1;
            B_double[i+j*n] = 1;
        }
    }
    if (print)
    {
        printf("Matrix A:\n");
        print_square_matrix(A, n);
        printf("Matrix B:\n");
        print_square_matrix(B, n);
        printf("Result:\n");
    }

    double start_time;
    double end_time;
    double elapsed_time;

    // printf("Nombre de thread : %d", omp_get_max_threads());

    // start_time = omp_get_wtime();
    // int **C = dac_square_mat_product(A, B, n);
    // if (print)
    //     print_square_matrix(C, n);
    // end_time = omp_get_wtime();
    // free_matrix(C, n);
    // elapsed_time = end_time - start_time; 
    // printf("DAC multiplication:                  %f seconds\n", elapsed_time);

    start_time = omp_get_wtime();
    int **CP = dac_square_mat_product_parra(A, B, n, 0);
    if (print)
        print_square_matrix(CP, n);
    end_time = omp_get_wtime();
    free_matrix(CP, n);
    elapsed_time = end_time - start_time;
    printf("DAC multiplication parra:            %f seconds\n", elapsed_time);// using %d threads\n", elapsed_time_parra, omp_get_num_procs());

    // start_time = omp_get_wtime();
    // int **S = dac_square_mat_product_strassen(A, B, n, 0);
    // if (print)
    //     print_square_matrix(S, n);
    // end_time = omp_get_wtime();
    // free_matrix(S, n);
    // elapsed_time = end_time - start_time;
    // printf("DAC multiplication Strassen:         %f seconds\n", elapsed_time);
    
    // start_time = omp_get_wtime();
    // int **SP = dac_square_mat_product_strassen_parra(A, B, n, 0);
    // if (print)
    //     print_square_matrix(SP, n);
    // end_time = omp_get_wtime();
    // free_matrix(SP, n);
    // elapsed_time = end_time - start_time;
    // printf("DAC multiplication Strassen parra:   %f seconds\n", elapsed_time);

    start_time = omp_get_wtime();
    int **SC = dac_square_mat_product_strassen_combined(A, B, n, 0, 512);
    if (print)
        print_square_matrix(SC, n);
    end_time = omp_get_wtime();
    // free_matrix(SC, n);
    elapsed_time = end_time - start_time;
    printf("DAC multiplication Strassen combined:%f seconds\n", elapsed_time);

    // start_time = omp_get_wtime();
    // int **D = square_mat_product(A, B, n);
    // if (print)
    //     print_square_matrix(D, n);
    // end_time = omp_get_wtime();
    // free_matrix(D, n);
    // elapsed_time = end_time - start_time;
    // printf("Standard multiplication:             %f seconds\n", elapsed_time);
    
    // start_time = omp_get_wtime();
    // int **DP = square_mat_product_parra(A, B, n);
    // if (print)
    //     print_square_matrix(DP, n);
    // end_time = omp_get_wtime();
    // // free_matrix(DP, n);
    // elapsed_time = end_time - start_time;
    // printf("Standard multiplication parra:       %f seconds\n", elapsed_time);

    start_time = omp_get_wtime();
    int **AT = dac_square_mat_product_alpha(A, B, n, 0, 512);
    if (print)
        print_square_matrix(AT, n);
    end_time = omp_get_wtime();
    // free_matrix(AT, n);
    elapsed_time = end_time - start_time;
    printf("DAC multiplication Alpha:            %f seconds\n", elapsed_time);

    openblas_set_num_threads(omp_get_max_threads());
    start_time = omp_get_wtime();
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                n, n, n, 1.0, A_double, n, B_double, n, 0.0, C_double, n);
    if (print)
        print_square_matrix(C_double, n);
    end_time = omp_get_wtime();
    // free_matrix(C_double, n);
    elapsed_time = end_time - start_time;
    printf("DAC multiplication cBLAS:            %f seconds\n", elapsed_time);

    if (is_matrix_equal(SC, AT, n))
        printf("Matrices are equal\n");
    else
        printf("Matrices are not equal\n");
    
    if (is_matrix_equal_in_Z2(SC, AT, n))
        printf("Matrices are equal in Z2\n");
    else
        printf("Matrices are not equal in Z2\n");

    free_matrix(SC, n);
    free_matrix(AT, n);

    
    free_matrix(A, n);
    free_matrix(B, n);

    return 0;
}
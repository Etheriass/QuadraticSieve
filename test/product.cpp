#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../src/Product/product.hpp"
#include "../src/Tools/tools.hpp"

int main()
{
    int n = 4;
    int ** A = (int **)malloc(n * sizeof(int*));
    for (int i = 0; i<n ; i++){
        A[i] = (int *)malloc(n * sizeof(int));
    }

    int ** B = (int **)malloc(n * sizeof(int*));
    for (int i = 0; i<n ; i++){
        B[i] = (int *)malloc(n * sizeof(int));
    }

    for (int i = 0; i<n ; i++){
        for (int j = 0; j<n ; j++){
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }

    printf("Matrix A:\n");
    print_square_matrix(A, n);
    printf("Matrix B:\n");
    print_square_matrix(B, n);

    // int* size = malloc(2 * sizeof(int));
    // size[0]=3;
    // size[1]=3;
    // int** r= mat_product(A,size, B, size);
    // print_square_matrix(r, 3);

    clock_t start, end;
    start = clock();

    int** s = square_mat_product(A,B,n);
    print_square_matrix(s, n);
    end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used); 

    start = clock();
    int** t = mat_4x4_product(A,B);
    print_square_matrix(t, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used); 
    
    start = clock();
    int** v = mat_4x4_product_alphatensor_Z2Z(A,B);
    print_square_matrix(t, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used); 

    // is_mat_equal(s,t,n);

    return(0);
}

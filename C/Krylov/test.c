#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Tools/tools.h"
#include "krylov.h"

int main(){
    int n = 3;
    int ** A = malloc(n * sizeof(int*));
    for (int i = 0; i<n ; i++){
        A[i] = malloc(n * sizeof(int));
    }

    for (int i = 0; i<n ; i++){
        for (int j = 0; j<n ; j++){
            A[i][j] = i+j;
        }
    }
    printf("A =\n");
    printMatrix(A, n,n);

    int* b = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        b[i] = 1;
    }

    clock_t start, end;
    start = clock();
    int*** K = krylov_subspace(A,b,n);

    printf("Krylov subspace of A and b :\n");
    for (int i = 0; i<n; i++){
        printMatrix(K[i],n,n);
    }

    end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);   

    return(0);
}
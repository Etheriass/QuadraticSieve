#include <stdlib.h>
#include <stdio.h>
#include "../Product/product.h"

int*** krylov_subspace(int** A, int*b, int n){

    int*** K = malloc(n * sizeof(int**));
    for (int i=0; i<n; i++){
        K[i] = malloc(n * sizeof(int*));
        for (int j = 0; j<n;j++){
            K[i][j] = malloc(n *sizeof(int));
        }
    }
    if (K == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // K[0]
    for (int i = 0; i<n; i++){
        K[0][i][0]= b[i];
        for (int j = 1; j<n; j++){
            K[0][i][j]= 0;
        }
    }

    // K[1]
    K[1] = square_mat_product(A, A, n);

    for (int i = 2; i<n; i++){
        K[i] = square_mat_product(K[i-1], A, n);
    }

    return K;
}
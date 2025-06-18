#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "../Product/product.hpp"
#include "../Tools/tools.hpp"

int** krylov_subspace_flat(int* A, int*b, int n){

    int** K = (int**)malloc(n * sizeof(int*));
    for (int i=0; i<n; i++){
        K[i] = (int*)malloc(n * n * sizeof(int));
    }
    if (K == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("%s", "Start\n");

    // K[0]
    for (int i = 0; i<n; i++){
        K[0][i*n + 0]= b[i];
        for (int j = 1; j<n; j++){
            K[0][i*n + j]= 0;
        }
    }
    printf("%s", "K0 done\n");

    // K[1]
    K[1] = square_mat_product_flat_parra(A, A, n);
    printf("%s", "K1 done\n");

    for (int i = 2; i<n; i++){
        printf("%d\n", i);
        K[i] = square_mat_product_flat_parra(K[i-1], A, n);
    }

    return K;
}

// int*** krylov_subspace(int** A, int*b, int n){

//     int*** K = (int***)malloc(n * sizeof(int**));
//     for (int i=0; i<n; i++){
//         K[i] = (int**)malloc(n * sizeof(int*));
//         for (int j = 0; j<n;j++){
//             K[i][j] = (int*)malloc(n *sizeof(int));
//         }
//     }
//     if (K == NULL){
//         fprintf(stderr, "Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }
//     printf("%s", "Start\n");

//     // K[0]
//     for (int i = 0; i<n; i++){
//         K[0][i][0]= b[i];
//         for (int j = 1; j<n; j++){
//             K[0][i][j]= 0;
//         }
//     }
//     printf("%s", "K0 done\n");

//     // K[1]
//     K[1] = square_mat_product(A, A, n);
//     printf("%s", "K1 done\n");

//     for (int i = 2; i<n; i++){
//         printf("%d\n", i);
//         K[i] = square_mat_product(K[i-1], A, n);
//     }

//     return K;
// }

std::vector<std::vector<int>> krylov_subspace(std::vector<int> A, std::vector<int> b, int n){
    // Initialize the vector of vectors with `n` vectors, each of size `b.size()`
    std::vector<std::vector<int>> K(n, std::vector<int>(b.size()));
    
    K[0] = b;

    for (int i = 1; i<n; i++){
        K[i] = mat_vect_product(A, b);
    }

    return K;
}
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <vector>
#include <iostream>
#include "product.hpp"

int** mat_product(int** A, int* shape_A, int** B, int* shape_B){
    // Check size of matrix
    if (shape_A[1] != shape_B[0]){
        printf("Invalid size : %dx%d and %dx%d", shape_A[0], shape_A[1], shape_B[0], shape_B[1]);
        exit(EXIT_FAILURE);
    }

    // Allocate result matrix
    int** M = (int**)malloc(shape_A[0] * sizeof(int*));
    for (int i =0; i< shape_B[1]; i++){
        M[i] = (int*)malloc(shape_B[1] * sizeof(int));
    }
    if (M == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Product
    int res = 0;
    for (int i = 0; i < shape_A[0]; i++){
        for (int j = 0; j < shape_B[1]; j++){
            res = 0;
            for (int k = 0; k < shape_A[1]; k++){
                res += A[i][k] * B[k][j];
            }
            M[i][j] = res;
        }
    }
    return M;
}

int** square_mat_product(int** A, int** B, int n){

    // Allocate result matrix
    int** M = (int**)malloc(n * sizeof(int*));
    for (int i =0; i< n; i++){
        M[i] = (int*)malloc(n * sizeof(int));
    }
    if (M == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Product
    int res = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            res = 0;
            for (int k = 0; k < n; k++){
                res += A[i][k] * B[k][j];
            }
            M[i][j] = res;
        }
    }
    return M;
}

int* square_mat_product_flat(int* A, int* B, int n){

    // Allocate result matrix
    int* M = (int*)malloc(n * n * sizeof(int));

    if (M == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Product
    int res = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            res = 0;
            for (int k = 0; k < n; k++){
                res += A[i*n + k] * B[k*n +j];
            }
            M[i*n + j] = res;
        }
    }
    return M;
}

int* square_mat_product_flat_parra(int* A, int* B, int n){

    // Allocate result matrix
    int* M = (int*)malloc(n * n * sizeof(int));

    if (M == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Product
    int res = 0;
    #pragma omp simd
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            res = 0;
            for (int k = 0; k < n; k++){
                res += A[i*n + k] * B[k*n +j];
            }
            M[i*n + j] = res;
        }
    }
    return M;
}

std::vector<int> mat_vect_product(std::vector<int> A, std::vector<int> b){
    int n = b.size();
    if (A.size() % n != 0){
        std::cout << "Wrong dimensions" << std::endl;
        return {};
    }
    std::vector<int> res(A.size() / n);
    int r;
    for (int i = 0; i < A.size() / n; i++){
        r = 0;
        for (int j = 0; j < n; j++){
            r += A[i*n + j] * b[j];
        }
        res[i] = r;
    }
    return res;
}

std::vector<int> mat_vect_product_F2(const std::vector<int> A, const std::vector<int> b){
    int n = b.size();
    if (A.size() % n != 0){
        std::cout << "Wrong dimensions" << std::endl;
        return {};
    }
    std::vector<int> res(A.size() / n);
    int r;
    for (int i = 0; i < A.size() / n; i++){
        r = 0;
        for (int j = 0; j < n; j++){
            // r += A[i*n + j] * b[j];
            r ^= (A[i*n + j] & b[j]);
        }
        res[i] = r;
    }
    return res;
}

std::vector<int> square_mat_product_cpp(std::vector<int> A, std::vector<int> B, int n){

    std::vector<int> M(n * n, 0); //Should be faster withou init to 0 but somehow it look faster with it (maybe compiler optimizations)

    // Product
    int res = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            res = 0;
            for (int k = 0; k < n; k++){
                res += A[i*n + k] * B[k*n + j];
            }
            M[i*n + j] = res;
        }
    }
    return M;
}

std::vector<int> square_mat_product_cpp_parra(std::vector<int> A, std::vector<int> B, int n){

    std::vector<int> M(n * n, 0); //Should be faster withou init to 0 but somehow it look faster with it (maybe compiler optimizations)
    // omp_set_num_threads(10);
    // Product
    int res = 0;
    #pragma omp simd
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            res = 0;
            for (int k = 0; k < n; k++){
                res += A[i*n + k] * B[k*n + j];
            }
            M[i*n + j] = res;
        }
    }
    return M;
}

int** square_mat_product_parra(int** A, int** B, int n){

    // Allocate result matrix
    int** M = (int**)malloc(n * sizeof(int*));
    for (int i =0; i< n; i++){
        M[i] = (int*)malloc(n * sizeof(int));
    }
    if (M == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Product
    int res = 0;
    int i, j;
    // #pragma omp parallel for private(i,j, res) shared(A, B, M, n)
    #pragma omp simd
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            res = 0;
            for (int k = 0; k < n; k++){
                res += A[i][k] * B[k][j];
            }
            M[i][j] = res;
        }
    }
    return M;
}

int** mat_4x4_product(int**A, int** B){
    int** M = (int**)malloc(4 * sizeof(int*));
    for (int i =0; i< 4; i++){
        M[i] = (int*)malloc(4 * sizeof(int));
    }
    if (M == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    M[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0] + A[0][3] * B[3][0];
    M[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1] + A[0][2] * B[2][1] + A[0][3] * B[3][1];
    M[0][2] = A[0][0] * B[0][2] + A[0][1] * B[1][2] + A[0][2] * B[2][2] + A[0][3] * B[3][2];
    M[0][3] = A[0][0] * B[0][3] + A[0][1] * B[1][3] + A[0][2] * B[2][3] + A[0][3] * B[3][3];

    M[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0] + A[1][2] * B[2][0] + A[1][3] * B[3][0];
    M[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1] + A[1][2] * B[2][1] + A[1][3] * B[3][1];
    M[1][2] = A[1][0] * B[0][2] + A[1][1] * B[1][2] + A[1][2] * B[2][2] + A[1][3] * B[3][2];
    M[1][3] = A[1][0] * B[0][3] + A[1][1] * B[1][3] + A[1][2] * B[2][3] + A[1][3] * B[3][3];

    M[2][0] = A[2][0] * B[0][0] + A[2][1] * B[1][0] + A[2][2] * B[2][0] + A[2][3] * B[3][0];
    M[2][1] = A[2][0] * B[0][1] + A[2][1] * B[1][1] + A[2][2] * B[2][1] + A[2][3] * B[3][1];
    M[2][2] = A[2][0] * B[0][2] + A[2][1] * B[1][2] + A[2][2] * B[2][2] + A[2][3] * B[3][2];
    M[2][3] = A[2][0] * B[0][3] + A[2][1] * B[1][3] + A[2][2] * B[2][3] + A[2][3] * B[3][3];

    M[3][0] = A[3][0] * B[0][0] + A[3][1] * B[1][0] + A[3][2] * B[2][0] + A[3][3] * B[3][0];
    M[3][1] = A[3][0] * B[0][1] + A[3][1] * B[1][1] + A[3][2] * B[2][1] + A[3][3] * B[3][1];
    M[3][2] = A[3][0] * B[0][2] + A[3][1] * B[1][2] + A[3][2] * B[2][2] + A[3][3] * B[3][2];
    M[3][3] = A[3][0] * B[0][3] + A[3][1] * B[1][3] + A[3][2] * B[2][3] + A[3][3] * B[3][3];

    return M;
}

int** mat_2x2_product(int**A, int** B){
    int** M = (int**)malloc(2 * sizeof(int*));
    for (int i =0; i< 2; i++){
        M[i] = (int*)malloc(2 * sizeof(int));
    }
    if (M == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    M[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    M[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    M[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    M[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];

    return M;
}

int** mat_2x2_product_strassen(int**A, int**B){
    int** M = (int**)malloc(2 * sizeof(int*));
    for (int i =0; i< 2; i++){
        M[i] = (int*)malloc(2 * sizeof(int));
    }
    if (M == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int P1 = A[0][0] * (B[0][1] - B[1][1]);
    int P2 = (A[0][0] + A[0][1]) * B[1][1];
    int P3 = (A[1][0] + A[1][1]) * B[0][0];
    int P4 = A[1][1] * (B[1][0] - B[0][0]);
    int P5 = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
    int P6 = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);
    int P7 = (A[0][0] - A[1][0]) * (B[0][0] + B[0][1]);

    M[0][0] = P5 + P4 - P2 + P6;
    M[0][1] = P1 + P2;
    M[1][0] = P3 + P4;
    M[1][1] = P5 + P1 - P3 - P7;

    return M;
}

int** mat_4x4_product_alphatensor_Z2Z(int**A, int** B){
    int** M = (int**)malloc(4 * sizeof(int*));
    for (int i = 0; i < 4; i++) {
        M[i] = (int*)malloc(4 * sizeof(int));
    }
    if (M == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    int h[47];
    h[0] = A[0][0] * B[0][2];
    h[1] = (A[0][0] + A[2][0] + A[2][2]) * (B[0][0] + B[2][0] + B[2][2]);
    h[2] = (A[0][0] + A[2][0] + A[2][3]) * (B[0][1] + B[3][1] + B[3][2]);
    h[3] = (A[0][2] + A[1][0] + A[1][2]) * (B[0][2] + B[0][3] + B[2][3]);
    h[4] = (A[0][0] + A[2][0]) * (B[0][0] + B[0][1] + B[0][2] + B[2][0] + B[2][2] + B[3][1] + B[3][2]);
    h[5] = (A[0][2] + A[1][2]) * (B[0][2] + B[0][3] + B[2][1] + B[2][2] + B[2][3] + B[3][1] + B[3][2]);
    h[6] = (A[0][3] + A[3][2] + A[3][3]) * (B[2][0] + B[2][2] + B[3][1]);
    h[7] = (A[0][3] + A[3][0] + A[3][3]) * (B[0][2] + B[0][3] + B[3][3]);
    h[8] = (A[0][2] + A[1][2] + A[1][3]) * (B[2][1] + B[3][1] + B[3][2]);
    h[9] = (A[0][3] + A[3][3]) * (B[0][2] + B[0][3] + B[2][1] + B[2][2] + B[3][0] + B[3][2] + B[3][3]);
    h[10] = A[2][2] * (B[0][0] + B[1][1] + B[1][2] + B[2][0] + B[2][1]);
    h[11] = (A[0][1] + A[2][1] + A[2][2]) * (B[1][1] + B[1][2] + B[2][1]);
    h[12] = A[2][3] * (B[0][1] + B[1][0] + B[1][2] + B[3][0] + B[3][1]);
    h[13] = (A[0][1] + A[2][1]) * (B[1][0] + B[1][1] + B[1][2] + B[2][1] + B[3][0]);
    h[14] = (A[0][1] + A[2][1] + A[2][3]) * (B[1][0] + B[1][2] + B[3][0]);
    h[15] = A[1][0] * (B[0][1] + B[0][3] + B[1][1] + B[1][2] + B[2][3]);
    h[16] = (A[0][1] + A[1][0] + A[1][1]) * (B[0][1] + B[1][1] + B[1][2]);
    h[17] = (A[0][1] + A[1][1]) * (B[0][1] + B[1][1] + B[1][2] + B[1][3] + B[3][3]);
    h[18] = A[1][3] * (B[1][2] + B[1][3] + B[2][1] + B[3][1] + B[3][3]);
    h[19] = (A[0][1] + A[1][2] + A[1][3] + A[2][0] + A[2][2]) * B[2][1];
    h[20] = (A[0][1] + A[1][1] + A[1][3]) * (B[1][2] + B[1][3] + B[3][3]);
    h[21] = A[3][2] * (B[1][2] + B[1][3] + B[2][0] + B[2][3] + B[3][0]);
    h[22] = (A[0][0] + A[0][2] + A[0][3] + A[1][2] + A[1][3] + A[2][0] + A[2][3]) * (B[3][1] + B[3][2]);
    h[23] = (A[0][1] + A[3][1] + A[3][2]) * (B[1][2] + B[1][3] + B[2][3]);
    h[24] = (A[0][1] + A[3][1]) * (B[0][0] + B[1][0] + B[1][2] + B[1][3] + B[2][3]);
    h[25] = (A[0][1] + A[3][1] + A[3][1]) * (B[0][0] + B[1][0] + B[1][2]);
    h[26] = A[0][3] * B[3][2];
    h[27] = (A[0][1] + A[1][0] + A[1][1] + A[2][0] + A[2][3]) * B[0][1];
    h[28] = (A[0][1] + A[1][0] + A[1][2] + A[3][1] + A[3][2]) * B[2][3];
    h[29] = (A[0][1] + A[2][0] + A[2][2] + A[3][0] + A[3][1]) * B[0][0];
    h[30] = A[3][0] * (B[0][0] + B[0][3] + B[1][0] + B[1][2] + B[3][3]);
    h[31] = (A[0][1] + A[2][1] + A[2][3] + A[3][2] + A[3][3]) * B[3][0];
    h[32] = (A[0][1] + A[1][1] + A[1][3] + A[3][0] + A[3][3]) * B[3][3];
    h[33] = (A[1][0] + A[2][0] + A[3][0]) * (B[0][0] + B[0][1] + B[0][3]);
    h[34] = (A[0][1] + A[1][0] + A[1][1] + A[2][1] + A[2][2]) * (B[1][1] + B[1][2]);
    h[35] = (A[0][1] + A[1][3] + A[2][1] + A[3][2]) * (B[1][2] + B[1][3] + B[2][1] + B[3][0]);
    h[36] = (A[0][1] + A[1][0] + A[2][2] + A[3][1]) * (B[0][0] + B[1][1] + B[1][2] + B[2][3]);
    h[37] = (A[1][1] + A[2][1] + A[3][1]) * (B[1][0] + B[1][1] + B[1][3]);
    h[38] = A[0][2] * B[1][2];
    h[39] = A[0][2] * B[2][2];
    h[40] = (A[0][0] + A[0][2] + A[0][3] + A[1][0] + A[1][2] + A[3][0] + A[3][3]) * (B[0][2] + B[0][3]);
    h[41] = (A[0][1] + A[2][1] + A[2][3] + A[3][0] + A[3][1]) * (B[1][0] + B[1][2]);
    h[42] = (A[1][3] + A[2][3] + A[3][3]) * (B[3][0] + B[3][1] + B[3][3]);
    h[43] = (A[1][2] + A[2][2] + A[3][2]) * (B[2][0] + B[2][1] + B[2][3]);
    h[44] = (A[0][0] + A[0][2] + A[0][3] + A[2][0] + A[2][2] + A[3][2] + A[3][3]) * (B[2][0] + B[2][2]);
    h[45] = (A[0][1] + A[1][1] + A[2][3] + A[3][0]) * (B[0][1] + B[1][0] + B[1][2] + B[3][3]);
    h[46] = (A[0][1] + A[1][1] + A[1][3] + A[3][1] + A[3][2]) * (B[1][2] + B[1][3]);

    // Calculate the resulting matrix M using the intermediate sums
    M[0][0] = h[14] + h[25] + h[1] + h[29] + h[31] + h[38] + h[39] + h[41] + h[44] + h[6];
    M[1][0] = h[10] + h[11] + h[13] + h[19] + h[21] + h[23] + h[24] + h[28] + h[34] + h[35] + h[36] + h[37] + h[43] + h[46];
    M[2][0] = h[10] + h[11] + h[13] + h[14] + h[25] + h[29] + h[38] + h[41];
    M[3][0] = h[14] + h[21] + h[23] + h[24] + h[25] + h[31] + h[38] + h[41];

    M[0][1] = h[11] + h[16] + h[19] + h[22] + h[26] + h[27] + h[34] + h[38] + h[2] + h[8];
    M[1][1] = h[11] + h[16] + h[17] + h[18] + h[19] + h[20] + h[34] + h[38];
    M[2][1] = h[11] + h[12] + h[13] + h[14] + h[16] + h[27] + h[34] + h[38];
    M[3][1] = h[12] + h[13] + h[14] + h[17] + h[18] + h[20] + h[31] + h[32] + h[35] + h[37] + h[41] + h[42] + h[45] + h[46];

    M[0][2] = h[0] + h[26] + h[38] + h[39];
    M[1][2] = h[15] + h[16] + h[17] + h[18] + h[20] + h[38] + h[39] + h[3] + h[5] + h[8];
    M[2][2] = h[10] + h[11] + h[12] + h[13] + h[14] + h[0] + h[1] + h[38] + h[2] + h[4];
    M[3][2] = h[9] + h[21] + h[23] + h[24] + h[25] + h[26] + h[30] + h[38] + h[6] + h[7];

    M[0][3] = h[0] + h[20] + h[23] + h[28] + h[32] + h[38] + h[40] + h[46] + h[3] + h[7];
    M[1][3] = h[15] + h[16] + h[17] + h[20] + h[23] + h[28] + h[38] + h[46];
    M[2][3] = h[15] + h[16] + h[17] + h[24] + h[25] + h[27] + h[29] + h[30] + h[33] + h[34] + h[36] + h[37] + h[41] + h[45];
    M[3][3] = h[20] + h[23] + h[24] + h[25] + h[30] + h[32] + h[38] + h[46];

    return M;
}
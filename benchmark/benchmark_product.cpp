#include <iostream>
#include <chrono>
#include <math.h>
#include <vector>
#include "../src/Product/product.hpp"
#include "../src/Tools/tools.hpp"


void benchmark(){

    int N = 4096;
    // int **A = allocate_square_matrix(N);
    // int **B = allocate_square_matrix(N);
    std::vector<int> A(N * N, 3);
    std::vector<int> B(N * N, 999);

    // for (int i = 0; i<N ; i++){
    //     for (int j = 0; j<N ; j++){
    //         A[i][j] = 1;
    //         B[i][j] = 1;
    //     }
    // }
    auto start = std::chrono::high_resolution_clock::now();

    // int** C = square_mat_product(A,B,N);
    // std::vector<int> C = square_mat_product_cpp(A,B,N);
    std::vector<int> C = square_mat_product_cpp_parra(A,B,N);
    // int** C = square_mat_product_parra(A,B,N);

    // for (int i = 0; i < N; ++i){
    //     for (int j = 0; j < N; ++j){
    //         printf("%d", C[i*N + j]);
    //     }
    // }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "============================\n";
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    std::cout << "============================\n";
}

int main(){
    benchmark();
    return 0;
}

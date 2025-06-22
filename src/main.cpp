#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <vector>
#include <random>
#include "Eratosthene/eratosthene.hpp"
#include "Friables/friables.hpp"
#include "Tools/tools.hpp"
#include "Factorization/factorization.hpp"
#include "Krylov/krylov.hpp"
#include "Product/dotProduct.hpp"


int main() {
    
    unsigned long long N = 17595551;//184467440737095601;;18446744073709551615
    printf("===============\n");
    printf("Quadratic Sieve\n");
    printf("===============\n");
    printf("Factorisation of %llu: \n", N);
    
    // Collection phase
    auto start_collection_phase = std::chrono::high_resolution_clock::now();
    int B = (int)exp(0.5*sqrt(log(N) * log(log(N)))) + 23;
    printf("Choosen B: %d\n", B);

    // Eratosthene sieve
    auto start_eratosthene = std::chrono::high_resolution_clock::now();
    std::vector<int> primes = eratostheneSieve(B);
    int piB = primes.size();
    auto end_eratosthene = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_eratosthene - start_eratosthene;
    std::cout << " - Eratosthene sieve took: " << elapsed.count() << " s\n";

    // Sieving
    int A = (int)sqrt(N)*1000;
    printf("Number of square to find: %d\n", piB);
    printf("Sieving interval: [%d, %d]\n", (int)sqrt(N) + 1, (int)sqrt(N) + A);
    
    auto start_sieving = std::chrono::high_resolution_clock::now();
    int nbQf;
    unsigned long long *Qf = QBfriablesV2Long(B, N, A, &nbQf);
    auto end_sieving = std::chrono::high_resolution_clock::now();
    elapsed = end_sieving - start_sieving;
    std::cout << " - QBfriable took: " << elapsed.count() << " s\n";
    printf("Number of Q-B-Friable numbers in [%d, %d]: %d\n", (int)sqrt(N) + 1, (int)sqrt(N) + A, nbQf);

    // Mod 2 factors Matrix building
    auto start_factor_matrix = std::chrono::high_resolution_clock::now();
    // std::vector<int> M(nbQf*piB, 0);
    std::vector<int> M(piB*piB, 0);

    for (int i = 0; i < piB; i++){
        std::vector<int> factorsPowers = factorsPowersMod2(Qf[i], primes);
        for (int j = 0; j < piB; j++){
            M[piB*i + j] = factorsPowers[j];
        }
    }
    auto end_factor_matrix = std::chrono::high_resolution_clock::now();
    elapsed = end_factor_matrix - start_factor_matrix;
    printf("Time taken to build the factor matrix: %f seconds\n", elapsed.count());
    // printMatrix(M, piB, piB);

    auto end_collection_phase  = std::chrono::high_resolution_clock::now();
    elapsed = end_collection_phase - start_collection_phase;
    printf("Time taken for the collection phase: %f seconds\n", elapsed.count());

    // Processing phase
    auto start_processing_phase = std::chrono::high_resolution_clock::now();

    // Krylov subspace
    std::vector<int> b (piB, 0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    for (int i = 0; i < b.size(); ++i) {
        b[i] = dis(gen);
    }
    std::vector<std::vector<int>> K = krylov_subspace(M, b, piB);

    // for (int i = 0; i < piB; i++){
    //     printMatrix(K[i], piB, 1);
    //     std::cout << std::endl;
    // }

    // Scalar Sequence
    std::vector<int> u (piB, 0);
    for (int i = 0; i < u.size(); ++i) {
        u[i] = dis(gen);
    }

    std::vector<int> S(piB, 0);
    for(int i = 0; i < piB; i++){
        S[i] = dot_product(u, K[i]);
        std::cout << S[i] << " ";
    }





    auto end_processing_phase = std::chrono::high_resolution_clock::now();
    elapsed = end_processing_phase - start_processing_phase;
    printf("Time taken for the proccessing phase: %f seconds\n", elapsed.count());


    free(Qf);

    return 0;
}
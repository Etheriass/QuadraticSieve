#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <vector>
#include <numeric>
#include <utility>
#include "Eratosthene/eratosthene.hpp"
#include "Friables/friables.hpp"
#include "Tools/tools.hpp"
#include "Tools/vectors.hpp"
#include "Factorization/factorization.hpp"
#include "Product/product.hpp"
#include "Wiedemann/wiedemann.hpp"

typedef unsigned long long ull;

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    ull N = 184467440737095601; // 1844671; 17595551;//184467440737095601;;18446744073709551615
    printf("===============\n");
    printf("Quadratic Sieve\n");
    printf("===============\n");
    printf("Factorisation of %llu: \n", N);

    // Collection phase
    auto start_collection_phase = std::chrono::high_resolution_clock::now();
    int B = (int)exp(0.5 * sqrt(log(N) * log(log(N))));
    printf("Choosen B: %d\n", B);

    // Eratosthene sieve
    auto start_eratosthene = std::chrono::high_resolution_clock::now();
    std::vector<int> primes = eratosthene_sieve(B); // See to do one eratosthene sieve (other in QBfriable but ull)
    int piB = primes.size();
    auto end_eratosthene = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_eratosthene - start_eratosthene;
    std::cout << " - Eratosthene sieve took: " << elapsed.count() << " s\n";

    // Sieving
    size_t A = (size_t)sqrt(N);
    printf("Number of square to find: %d\n", piB);
    printf("Sieving interval: [%llu, %llu]\n", (ull)sqrt(N) + 1, (ull)sqrt(N) + A);

    auto start_sieving = std::chrono::high_resolution_clock::now();
    std::pair<std::vector<ull>, std::vector<ull>> QfX = QBfriablesV2Long(N, A, primes);
    std::vector<ull> Qf = QfX.first; // Q-B-Friable numbers
    std::vector<ull> X = QfX.second; // Corresponding X values
    int nbQf = Qf.size();
    auto end_sieving = std::chrono::high_resolution_clock::now();
    elapsed = end_sieving - start_sieving;
    std::cout << " - QBfriable took: " << elapsed.count() << " s\n";
    printf("Number of Q-B-Friable numbers in [%llu, %llu]: %d\n", (ull)sqrt(N) + 1, (ull)sqrt(N) + A, nbQf);

    // Mod 2 factors Matrix building
    auto start_factor_matrix = std::chrono::high_resolution_clock::now();
    std::vector<int> M(nbQf * piB, 0);
    std::vector<std::vector<int>> fullExp(nbQf, std::vector<int>(piB));
    for (int i = 0; i < nbQf; i++)
    {
        std::vector<int> factorsPowers = factors_powers(Qf[i], primes);
        for (int j = 0; j < piB; j++)
        {
            fullExp[i][j] = factorsPowers[j];
            M[piB * i + j] = factorsPowers[j] % 2;
        }
    }

    auto end_factor_matrix = std::chrono::high_resolution_clock::now();
    elapsed = end_factor_matrix - start_factor_matrix;
    printf("Time taken to build the factor matrix: %f seconds\n", elapsed.count());

    auto end_collection_phase = std::chrono::high_resolution_clock::now();
    elapsed = end_collection_phase - start_collection_phase;
    printf("Time taken for the collection phase: %f seconds\n", elapsed.count());

    // Processing phase
    auto start_processing_phase = std::chrono::high_resolution_clock::now();

    std::vector<int> M_T = transpose(M, nbQf, piB);
    std::vector<int> MM_T = mat_product_f2(M, M_T, nbQf, piB);
    
    auto start_kernel_search = std::chrono::high_resolution_clock::now();
    std::vector<int> w = wiedemann(MM_T, nbQf, 1000);
    auto end_kernel_search = std::chrono::high_resolution_clock::now();
    elapsed = end_kernel_search - start_kernel_search;
    printf("Time taken for the kernel search: %f seconds\n", elapsed.count());

    __uint128_t aa = 1, bb = 1;
    for (int i = 0; i < nbQf; i++)
    {
        if (w[i] == 1)
            aa = (aa * X[i]) % N;
    }

    std::vector<int> E(piB, 0);
    for(int i = 0; i < nbQf; ++i){
        if(!w[i]) continue;
            for(int j = 0; j < piB; ++j)
                E[j] += fullExp[i][j];
    }

    for(int j = 0; j < piB; ++j){
        int half = E[j]/2;
        while(half--) 
            bb = (bb * primes[j]) % N;
    }


    std::cout << "a = " << ull(aa) << ", b = " << ull(bb) << std::endl;
    std::cout << "a+b = " << (ull(aa) + ull(bb)) % N << ", b-a = " << (ull(bb) + N - ull(aa)) % N << std::endl;

    ull gcd1 = std::gcd((bb + N - aa) % N, N);
    ull gcd2 = std::gcd((aa + bb) % N, N);
    std::cout << "Factor found: {" << gcd1 << ", " << gcd2 << "}" << std::endl;
    if ((gcd1 == 1 && gcd2 == 1) || (gcd1 == 1 && gcd2 == N) || (gcd1 == N && gcd2 == 1) || (gcd1 == N && gcd2 == N))
    {
        std::cout << "FAIL: {" << gcd1 << ", " << gcd2 << "} are trivial factor of " << N << std::endl;
    }
    else
    {
        if (N % gcd1 == 0 && gcd1 != 1 && gcd1 != N)
            std::cout << "SUCCESS: " << gcd1 << " is a non-trivial factor of " << N << std::endl;
        if (N % gcd2 == 0 && gcd2 != 1 && gcd2 != N)
            std::cout << "SUCCESS: " << gcd2 << " is a non-trivial factor of " << N << std::endl;
    }

    auto end_processing_phase = std::chrono::high_resolution_clock::now();
    elapsed = end_processing_phase - start_processing_phase;
    printf("Time taken for the proccessing phase: %f seconds\n", elapsed.count());

    auto end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    printf("Total time taken: %f seconds\n", elapsed.count());

    return 0;
}
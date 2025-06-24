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
    for (int i = 0; i < nbQf; i++){
        std::vector<int> factorsPowers = factors_powers_f2(Qf[i], primes);
        for (int j = 0; j < piB; j++){
            M[piB*i + j] = factorsPowers[j];
        }
    }

    auto end_factor_matrix = std::chrono::high_resolution_clock::now();
    elapsed = end_factor_matrix - start_factor_matrix;
    printf("Time taken to build the factor matrix: %f seconds\n", elapsed.count());
    // printMatrix(M, nbQf, piB);

    auto end_collection_phase = std::chrono::high_resolution_clock::now();
    elapsed = end_collection_phase - start_collection_phase;
    printf("Time taken for the collection phase: %f seconds\n", elapsed.count());

    // Processing phase
    auto start_processing_phase = std::chrono::high_resolution_clock::now();
    // std::vector<int> M_T = transpose(M, nbQf, piB);
    // // printMatrix(M_T, piB, nbQf);
    // std::vector<int> MM_T = mat_product_f2(M, M_T, nbQf, piB);
    // // printf("Matrix MM_T:\n");
    // // printMatrix(MM_T, nbQf, nbQf);

    int m = primes.size();
    int r = Qf.size();  
    std::vector<int> MA(r*r);
    for(int i=0; i<r; ++i) {
        for(int ip=0; ip<r; ++ip) {
            int acc = 0;
            for(int j=0; j<m; ++j)
                acc ^= (M[i*m + j] & M[ip*m + j]);
            MA[i*r + ip] = acc;
        }
    }

    std::vector<int> w;
    try
    {
        w = wiedemann(MA, nbQf, 1000);

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(EXIT_FAILURE);
    }


    ull a = 1;
    // __uint128_t b = 1;
    for (int i = 0; i < nbQf; i++)
    {
        if (w[i] == 1)
        {
            a = (a * X[i]) % N;
            // b = (b * Qf[i]);
        }
    }
    // b = (ull)sqrt(b);
    // ull sqrt_b = (ull)sqrt(b);

    // printf("%llu = %llu\n", b, sqrt_b*sqrt_b);

    std::vector<int> expo(m, 0);
    for(int i = 0; i < r; ++i) {
        if (!w[i]) continue;
        for(int j = 0; j < m; ++j)
            expo[j] += M[i*m + j];
    }

    // Now each expo[j] is even (because w is a dependency).
    // Build b = ∏ prime[j]^(expo[j]/2) mod N:
    __uint128_t bb = 1;
    for(int j = 0; j < m; ++j) {
        int half = expo[j] / 2;
        while(half--) {
            bb = (bb * primes[j]) % N;
        }
    }
    ull b = ull(bb);

    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "a+b = " << (a + b) << ", b-a = " << (b - a) << std::endl;

    // __uint128_t bma = (__uint128_t)b - (__uint128_t)a;
    // __uint128_t apb = (__uint128_t)a + (__uint128_t)b;
    // __uint128_t N128 = (__uint128_t)N;
    // ull gcd1 = std::gcd(bma, N128);
    // ull gcd2 = std::gcd(apb, N128);

    ull gcd1 = std::gcd((b + N - a)%N, N);
    ull gcd2 = std::gcd(a + b, N);
    std::cout << "Factor found: {" << gcd1 << ", " << gcd2 << "}" << std::endl;
    if (gcd1 == 1 & gcd2 == 1)
    {
        std::cout << "FAIL: {" << gcd1 << ", " << gcd2 << "} are trivial factor of " << N << std::endl;
    }
    else
    {
        if (N % gcd1 == 0 & gcd1 != 1)
            std::cout << "SUCCESS: " << gcd1 << " is a non-trivial factor of " << N << std::endl;
        if (N % gcd2 == 0 & gcd2 != 1)
            std::cout << "SUCCESS: " << gcd2 << " is a non-trivial factor of " << N << std::endl;
    }

    auto end_processing_phase = std::chrono::high_resolution_clock::now();
    elapsed = end_processing_phase - start_processing_phase;
    printf("Time taken for the proccessing phase: %f seconds\n", elapsed.count());

    return 0;
}
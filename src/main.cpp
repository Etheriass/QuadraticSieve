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
    // for (int i = 0; i < nbQf; i++){
    //     printf("{%llu, %llu}, ", X[i], Qf[i]);
    // }
    // printf("\n");

    // Mod 2 factors Matrix building
    auto start_factor_matrix = std::chrono::high_resolution_clock::now();
    std::vector<int> M(piB * piB, 0);
    for (int i = 0; i < piB; i++){
        std::vector<int> factorsPowers = factors_powers_f2(Qf[i], primes);
        for (int j = 0; j < piB; j++){
            M[piB*i + j] = factorsPowers[j];
        }
    }

    // int removed = 0;
    // for (int i = 0; i < nbQf; i++)
    // {
    //     if (i - removed > piB - 1)
    //     {
    //         break;
    //     }
    //     std::vector<int> factors_powers = factors_powers_f2(Qf[i], primes);
    //     // print_row_vec(factors_powers);
    //     if (nbQf - removed > piB)
    //     {
    //         if (sum_vec(factors_powers) < 5)
    //         {
    //             // printf("REMOVED");
    //             removed++;
    //             continue;
    //         }
    //     }
    //     // printf("%d:, %d removed\n", i, removed);

    //     for (int j = 0; j < piB; j++)
    //     {
    //         M[piB * (i - removed) + j] = factors_powers[j];
    //     }
    // }
    // printf("%d removed\n", removed);

    auto end_factor_matrix = std::chrono::high_resolution_clock::now();
    elapsed = end_factor_matrix - start_factor_matrix;
    printf("Time taken to build the factor matrix: %f seconds\n", elapsed.count());
    // printMatrix(M, piB, piB);

    auto end_collection_phase = std::chrono::high_resolution_clock::now();
    elapsed = end_collection_phase - start_collection_phase;
    printf("Time taken for the collection phase: %f seconds\n", elapsed.count());

    // Processing phase
    auto start_processing_phase = std::chrono::high_resolution_clock::now();
    std::vector<int> M_T = transpose(M, piB, piB);
    // printMatrix(M_T, piB, piB);
    std::vector<int> w = wiedemann(M_T, piB, 1000);
    // print_row_vec(w);

    int a = 1;
    ull b = 1;
    for (int i = 0; i < piB; i++)
    {
        if (w[i] == 1)
        {
            a = (a * X[i]) % N;
            b = (b * Qf[i]);
        }
    }
    b = (ull)sqrt(b);
    std::cout << "a = " << a << ", b = " << b << std::endl;

    int gcd1 = std::gcd(abs(a - (int)b), N);
    int gcd2 = std::gcd(a + (int)b, N);
    std::cout << "Factor found: {" << gcd1 << ", " << gcd2 << "}" << std::endl;
    if (gcd1 == 1 & gcd2 == 1)
    {
        std::cout << "FAIL: {" << gcd1 << ", " << gcd2 << "}" << "are trivial factor of " << N << std::endl;
    }
    else
    {
        if (N % gcd1 == 0 & gcd1 != 1)
            std::cout << "SUCCESS: " << gcd1 << " is a non-trivial factor of " << N << std::endl;
        if (N % gcd2 == 0 & gcd1 != 1)
            std::cout << "SUCCESS: " << gcd2 << " is a non-trivial factor of " << N << std::endl;
    }

    auto end_processing_phase = std::chrono::high_resolution_clock::now();
    elapsed = end_processing_phase - start_processing_phase;
    printf("Time taken for the proccessing phase: %f seconds\n", elapsed.count());

    return 0;
}
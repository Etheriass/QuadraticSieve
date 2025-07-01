#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include <numeric> // For std::gcd
#include <utility> // For std::pair
#include "Eratosthene/eratosthene.hpp"
#include "Friables/friables.hpp"
#include "Tools/tools.hpp"
#include "Tools/vectors.hpp"
#include "Factorization/factorization.hpp"
#include "Product/product.hpp"
#include "Wiedemann/wiedemann.hpp"
#include "Legendre/legendre.hpp"

typedef unsigned long long ull;
using Clock = std::chrono::steady_clock; // guaranteed monotonic, not affected by system clock changes

int main()
{
    std::cout << "Quadratic Sieve Factorization" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    auto start = Clock::now();
    constexpr ull N = 184467440737095601; // 1844671; 17595551;//184467440737095601;;18446744073709551615
    std::cout << "N = " << N << std::endl;

    // Collection phase
    auto start_collection_phase = Clock::now();
    const int B = (int)exp(0.5 * sqrt(log(N) * log(log(N))));
    std::cout << "Choosen B: " << B << std::endl;

    // Eratosthene sieve
    auto start_eratosthene = Clock::now();
    std::vector<int> primes = eratosthene_sieve(B);
    auto end_eratosthene = Clock::now();
    std::chrono::duration<double> dur_eratosthene = end_eratosthene - start_eratosthene;
    std::cout << "pi(B) = " << primes.size() << std::endl;
    
    // Factor base
    std::vector<int> factor_base;
    for (const int prime: primes){
        if (legendre_long(N, prime)==1)
            factor_base.push_back(prime);
    }
    std::cout << "Factor base reduced from " << primes.size() << " to " << factor_base.size() << " elements" << std::endl;
    const int factor_base_size = factor_base.size();
    std::cout << "Number of relations to find: " << factor_base_size << std::endl;

    // Sieving
    auto start_sieving = Clock::now();
    int number_of_relations = 0, iter = 0;
    size_t A = (size_t)(B*log(B));
    std::pair<std::vector<ull>, std::vector<ull>> QfX;
    std::vector<ull> Qf, X;
    while (number_of_relations <= 1.5*factor_base_size)
    {
        std::cout << "Iteration " << iter << ": A = " << A << std::endl;
        QfX = QBfriablesV2Long(N, A, factor_base);
        Qf = QfX.first; // Q-B-Friable numbers
        X = QfX.second; // Corresponding X values
        number_of_relations = Qf.size();
        A *= 10;
        iter++;
        if (iter > 10)
        {
            std::cout << "Too many iterations, stopping sieving." << std::endl;
            break;
        }
    }
    
    auto end_sieving = Clock::now();
    std::chrono::duration<double> dur_sieving = end_sieving - start_sieving;
    std::cout << "Found " << number_of_relations << " relations" << std::endl;

    // Mod 2 factors Matrix building
    auto start_factor_matrix = Clock::now();
    std::vector<int> M(number_of_relations * factor_base_size);
    std::vector<std::vector<int>> fullExp(number_of_relations, std::vector<int>(factor_base_size));
    std::vector<int> factorsPowers(factor_base_size);
    for (int i = 0; i < number_of_relations; i++)
    {
        factorsPowers = factors_powers(Qf[i], factor_base);
        for (int j = 0; j < factor_base_size; j++)
        {
            fullExp[i][j] = factorsPowers[j];
            M[factor_base_size * i + j] = factorsPowers[j] % 2;
        }
    }
    auto end_factor_matrix = Clock::now();
    std::chrono::duration<double> dur_factor_matrix = end_factor_matrix - start_factor_matrix;

    auto end_collection_phase = Clock::now();
    std::chrono::duration<double> dur_collection_phase = end_collection_phase - start_collection_phase;

    // Processing phase
    auto start_processing_phase = Clock::now();
    std::vector<int> M_T = transpose(M, number_of_relations, factor_base_size);
    std::vector<int> MM_T = mat_product_f2(M, M_T, number_of_relations, factor_base_size);
    
    auto start_kernel_search = Clock::now();
    std::vector<int> w = wiedemann(MM_T, number_of_relations, 100);
    auto end_kernel_search = Clock::now();
    std::chrono::duration<double> dur_kernel_search = end_kernel_search - start_kernel_search;

    __uint128_t aa = 1, bb = 1;
    std::vector<int> exponents(factor_base_size, 0);
    for (int i = 0; i < number_of_relations; i++)
    {
        if (w[i] == 1){
            aa = (aa * X[i]) % N;
            for(int j = 0; j < factor_base_size; j++)
                exponents[j] += fullExp[i][j];
        }
    }

    for(int j = 0; j < factor_base_size; j++){
        int half = exponents[j]/2;
        while(half--) 
            bb = (bb * factor_base[j]) % N;
    }


    std::cout << "a = " << ull(aa) << ", b = " << ull(bb) << std::endl;
    std::cout << "a+b = " << (ull(aa + bb)) % N << ", b-a = " << (ull(bb) + N - ull(aa)) % N << std::endl;

    ull gcd1 = (ull)std::gcd((bb + N - aa) % N, N);
    ull gcd2 = (ull)std::gcd((aa + bb) % N, N);
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

    auto end_processing_phase = Clock::now();
    std::chrono::duration<double> dur_processing_phase = end_processing_phase - start_processing_phase;

    auto end = Clock::now();
    std::chrono::duration<double> dur_total = end - start;

    // Timings
    std::cout << "TIMINGS:" << std::endl;
    std::cout << "Collection phase took: " << dur_collection_phase.count() << " s" << std::endl;
    std::cout << "- Eratosthene sieve took: " << dur_eratosthene.count() << " s" << std::endl;
    std::cout << "- Sieving took: " << dur_sieving.count() << " s" << std::endl;
    std::cout << "- Factor matrix building took: " << dur_factor_matrix.count() << " s" << std::endl;
    std::cout << "Processing phase took: " << dur_processing_phase.count() << " s" << std::endl;
    std::cout << "- Kernel search took: " << dur_kernel_search.count() << " s" << std::endl;
    std::cout << "Total time: " << dur_total.count() << " s" << std::endl;

    return 0;
}
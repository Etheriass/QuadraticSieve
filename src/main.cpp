#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>
#include "Eratosthene/eratosthene.hpp"
#include "Friables/friables.hpp"
#include "Tools/tools.hpp"
#include "Tools/vectors.hpp"
#include "Tools/matrix.hpp"
#include "Factorization/factorization.hpp"
#include "Product/product.hpp"
#include "Wiedemann/wiedemann.hpp"
#include "Legendre/legendre.hpp"

#ifdef USE_OPENMP
#include <omp.h>
#endif

using Clock = std::chrono::steady_clock; // guaranteed monotonic, not affected by system clock changes

__uint128_t slow_mod_mul(__uint128_t a, __uint128_t b, __uint128_t mod)
{
    if (a == 0 || b == 0)
        return 0;
    a %= mod;
    b %= mod;

    __uint128_t result = 0;
    while (b > 0)
    {
        if (b & 1)
        {
            // Add a to result, handling overflow
            __uint128_t temp = mod - result;
            if (a >= temp)
                result = a - temp;
            else
                result += a;
        }

        // Double a, handling overflow
        __uint128_t temp = mod - a;
        if (a >= temp)
            a = a - temp;
        else
            a += a;

        b >>= 1;
    }
    return result;
}

__uint128_t safe_mod_mul(__uint128_t a, __uint128_t b, __uint128_t mod)
{
    __uint128_t prod;
    // GCC/Clang builtin to detect overflow:
    if (__builtin_mul_overflow(a, b, &prod))
        return slow_mod_mul(a, b, mod);
    else
        return prod % mod;
}

int main()
{ // uint128 max value: 340282366920938463463374607431768211455
    auto start = Clock::now();
    const __uint128_t N = parse_u128("340282366920938463463374607431768211439"); // 1844671; 17595551; 18446744073709551615; 340282366920938463463374607431768211451
    const int B = (int)exp(0.5 * sqrt(log(N) * log(log(N))));
    print_header(N, B);

    // Eratosthene sieve
    auto start_eratosthene = Clock::now();
    std::vector<int> primes = eratosthene_sieve(B);
    auto end_eratosthene = Clock::now();
    std::chrono::duration<double> dur_eratosthene = end_eratosthene - start_eratosthene;
    std::cout << "Collection phase:\npi(B) = " << primes.size() << std::endl;

    // Factor base
    std::vector<int> factor_base;
    for (const int prime : primes)
    {
        if (legendre_128(N, prime) == 1)
            factor_base.push_back(prime);
    }
    std::cout << "Factor base reduced from " << primes.size() << " to " << factor_base.size() << " elements" << std::endl;
    const int factor_base_size = factor_base.size();
    std::cout << "Number of relations to find: " << factor_base_size << std::endl;

    // Sieving
    auto start_sieving = Clock::now();
    int number_of_relations = 0, iter = 0;
    size_t A = (size_t)(1000 * B * log(B));
    std::vector<__uint128_t> Qf, X;
    while (number_of_relations < 1 * factor_base_size && iter < 10)
    {
        std::cout << " Sieve " << iter + 1 << ": interval size = " << A << std::endl;
        std::tie(Qf, X) = Q_B_friables_128(N, A, factor_base);
        number_of_relations = Qf.size();
        std::cout << "Found " << number_of_relations << " relations" << std::endl;
        A *= 3, iter++;
    }
    auto end_sieving = Clock::now();
    std::chrono::duration<double> dur_sieving = end_sieving - start_sieving;

    // Mod 2 factors Matrix filling
    auto start_factor_matrix = Clock::now();
    std::vector<char> M(number_of_relations * factor_base_size);
    std::vector<std::vector<int>> full_exponents(number_of_relations, std::vector<int>(factor_base_size));
    std::vector<int> powers(factor_base_size);
    for (int i = 0; i < number_of_relations; i++)
    {
        powers = factors_powers(Qf[i], factor_base);
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
        for (int j = 0; j < factor_base_size; j++)
        {
            full_exponents[i][j] = powers[j];
            M[factor_base_size * i + j] = powers[j] % 2;
        }
    }
    auto end_factor_matrix = Clock::now();
    std::chrono::duration<double> dur_factor_matrix = end_factor_matrix - start_factor_matrix;
    std::chrono::duration<double> dur_collection_phase = end_factor_matrix - start_eratosthene;

    // Processing phase
    auto start_processing_phase = Clock::now();
    std::cout << "\nProcessing phase:\n";
    std::vector<char> M_T = transpose(M, number_of_relations, factor_base_size);
    std::vector<char> MM_T = mat_product_f2(M, M_T, number_of_relations, factor_base_size);
    auto end_matrix_construction = Clock::now();
    std::chrono::duration<double> dur_matrix_construction = end_matrix_construction - start_processing_phase;


    std::chrono::_V2::steady_clock::time_point start_kernel_search;
    std::chrono::_V2::steady_clock::time_point start_solution_computation;
    std::chrono::duration<double> dur_kernel_search;
    bool solution_is_found = false;
    while (!solution_is_found)
    {
        // Kernel search using Wiedemann algorithm
        start_kernel_search = Clock::now();
        std::vector<char> w = wiedemann(MM_T, number_of_relations, 100);
        auto end_kernel_search = Clock::now();
        dur_kernel_search = end_kernel_search - start_kernel_search;

        start_solution_computation = Clock::now();
        __uint128_t a = 1, b = 1;
        std::vector<int> exponents(factor_base_size, 0);
        for (int i = 0; i < number_of_relations; i++)
        {
            if (w[i] == 1)
            {
                // a = (a * X[i]) % N;
                a = safe_mod_mul(a, X[i], N);
                for (int j = 0; j < factor_base_size; j++)
                    exponents[j] += full_exponents[i][j];
            }
        }

        for (int j = 0; j < factor_base_size; j++)
        {
            int half = exponents[j] / 2;
            while (half--)
                b = safe_mod_mul(b, factor_base[j], N);
            // b = (b * factor_base[j]) % N;
        }

        __uint128_t gcd1 = b >= a ? gcd_128((b - a) % N, N) : gcd_128((a - b) % N, N);
        __uint128_t gcd2 = gcd_128((a + b) % N, N);
        solution_is_found = solution(N, a, b, gcd1, gcd2);
    }
    // Computation phase timing is wrong
    auto end_solution_computation = Clock::now();
    std::chrono::duration<double> dur_solution_computation = end_solution_computation - start_solution_computation;
    std::chrono::duration<double> dur_processing_phase = end_solution_computation - start_processing_phase;

    auto end = Clock::now();
    std::chrono::duration<double> dur_total = end - start;

    print_timings(dur_collection_phase, dur_eratosthene, dur_sieving, dur_factor_matrix, dur_processing_phase, dur_matrix_construction, dur_kernel_search, dur_solution_computation, dur_total);

    return EXIT_SUCCESS;
}
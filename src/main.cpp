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
#include "Solution/solution.hpp"

using Clock = std::chrono::steady_clock;
using duration = std::chrono::duration<double>;

// uint128 max value: 340282366920938463463374607431768211455

int main(int argc, char* argv[])
{  
    auto start = Clock::now();
    const __uint128_t N = parse_u128(argc > 1 ? argv[1] : "340282366920938463463374607431768211439"); // 17595551; 18446744073709551615; 5316911983139663487003542222693990401
    const int B = (int)exp(0.5 * sqrt(log(N) * log(log(N))));
    print_header(N, B);

    // Eratosthene sieve
    auto start_eratosthene = Clock::now();
    std::vector<int> primes = eratosthene_sieve(B);
    auto end_eratosthene = Clock::now();
    duration dur_eratosthene = end_eratosthene - start_eratosthene;
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
    size_t A = (size_t)(10 * B * log(B));
    std::vector<__uint128_t> Qf, X;
    while (number_of_relations <= 2 * factor_base_size && A < 1e8)
    {
        std::cout << " Sieve " << iter + 1 << ": interval size = " << A << std::endl;
        std::tie(Qf, X) = Q_B_friables_128(N, A, factor_base);
        number_of_relations = Qf.size();
        std::cout << "Found " << number_of_relations << " relations" << std::endl;
        A *= 2, iter++;
        if (iter > 20)
        {
            std::cout << "Too many iterations, stopping sieving: choose a larger interval size." << std::endl;
            break;
            // return EXIT_FAILURE;
        }
    }
    auto end_sieving = Clock::now();
    duration dur_sieving = end_sieving - start_sieving;

    // Mod 2 factors Matrix filling
    auto start_factor_matrix = Clock::now();
    std::vector<char> M(number_of_relations * factor_base_size);
    std::vector<std::vector<int>> full_exponents(number_of_relations, std::vector<int>(factor_base_size));
    std::vector<int> powers(factor_base_size);
    for (int i = 0; i < number_of_relations; i++)
    {
        powers = factors_powers(Qf[i], factor_base);
        for (int j = 0; j < factor_base_size; j++)
        {
            full_exponents[i][j] = powers[j];
            M[factor_base_size * i + j] = powers[j] % 2;
        }
    }
    auto end_factor_matrix = Clock::now();
    duration dur_factor_matrix = end_factor_matrix - start_factor_matrix;
    duration dur_collection_phase = end_factor_matrix - start_eratosthene;

    // Processing phase
    auto start_processing_phase = Clock::now();
    std::cout << "\nProcessing phase:\n";
    std::vector<char> M_T = transpose(M, number_of_relations, factor_base_size);
    std::vector<char> MM_T = mat_product_f2_reorder(M, M_T, number_of_relations);
    auto end_matrix_construction = Clock::now();
    duration dur_matrix_construction = end_matrix_construction - start_processing_phase;

    // Kernel search using Wiedemann algorithm
    duration dur_kernel_search(0);
    duration dur_solution_computation(0);
    bool solution_is_found = false;
    while (!solution_is_found)
    {
        auto start_kernel_search = Clock::now();
        std::vector<char> w = wiedemann(MM_T, number_of_relations, 10);
        auto end_kernel_search = Clock::now();
        dur_kernel_search += end_kernel_search - start_kernel_search;

        auto start_solution_computation = Clock::now();
        __uint128_t a = a_computation(w, X, N);
        __uint128_t b = b_computation(full_exponents, factor_base, w, N);
        solution_is_found = solution(N, a, b);
        auto end_solution_computation = Clock::now();
        dur_solution_computation += end_solution_computation - start_solution_computation;
    }
    auto end = Clock::now();
    duration dur_processing_phase = end - start_processing_phase;
    duration dur_total = end - start;

    print_timings(dur_collection_phase,
                  dur_eratosthene,
                  dur_sieving,
                  dur_factor_matrix,
                  dur_processing_phase,
                  dur_matrix_construction,
                  dur_kernel_search,
                  dur_solution_computation,
                  dur_total);

    return EXIT_SUCCESS;
}
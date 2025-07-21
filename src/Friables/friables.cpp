#include <vector>
#include <utility>
#include "friables.hpp"
#include "../Eratosthene/eratosthene.hpp"
#include "../Tools/tools.hpp"
#include "../Legendre/legendre.hpp"

#ifdef USE_OPENMP
#include <omp.h>
#endif

std::pair<std::vector<__uint128_t>, std::vector<__uint128_t>> Q_B_friables_128(__uint128_t N, size_t A, const std::vector<int> &factor_base)
{
    const __uint128_t r = sqrt_128(N) + 1;
    std::vector<__uint128_t> Q(A);

#ifdef USE_OPENMP
#pragma omp parallel for
#endif
    for (size_t i = 0; i < A; i++)
    {
        Q[i] = (r + i) * (r + i) - N; // Q(x) = (x + sqrt(N))^2 - N
        // while ((Q[i] & 1) == 0) Q[i] >>= 1; // Remove all factors of 2
        Q[i] >>= __builtin_ctzll(Q[i]); // Remove all factors of 2 using count trailing zeros
    }

    for (size_t pk : factor_base)
    {
        if (pk == 2)
            continue;
        int j = 0;
        int a1 = -1, a2 = -1;

        while (j < A) // Find both index where Q[j] == 0 mod pk
        {
            if (Q[j] % pk == 0)
            {
                if (a1 == -1)
                {
                    a1 = j;
                }
                else
                {
                    a2 = j;
                    break;
                }
            }
            j++;
        }
        const int ecart = a2 - a1;
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
        for (size_t k = a1; k < A - ecart; k += pk) // There is only 2 multiples of pk by interval of pk
        {
            while (Q[k] > 1 && Q[k] % pk == 0)
            {
                Q[k] = Q[k] / pk;
            }
            while (Q[k + ecart] > 1 && Q[k + ecart] % pk == 0)
            {
                Q[k + ecart] = Q[k + ecart] / pk;
            }
        }
    }

    std::vector<__uint128_t> Qf; // Q-B-Friable numbers
    std::vector<__uint128_t> X;  // Corresponding X values

    for (size_t i = 0; i < A; i++)
    {
        if (Q[i] == 1)
        {
            Qf.push_back((r + i) * (r + i) - N);
            X.push_back((r + i));
        }
    }
    return {Qf, X};
}

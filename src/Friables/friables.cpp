#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <utility>
#include "friables.hpp"
#include "../Eratosthene/eratosthene.hpp"

typedef unsigned long long ull;

std::pair<std::vector<ull>, std::vector<ull>> QBfriablesV2Long(const ull N, const size_t A, const std::vector<int> &factor_base)
{
    const ull range_start = (ull)sqrt(N) + 1;
    std::vector<ull> Q(A), Qf, X;
    Qf.reserve(A); // Reserve space but do not initialize the elements
    X.reserve(A);

    for (size_t i = 0; i < A; i++)
    {
        Q[i] = (range_start + i) * (range_start + i) - N; // Q(x) = (x + sqrt(N))^2 - N
    }

    for (size_t pk : factor_base)
    {
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

    for (size_t i = 0; i < A; i++)
    {
        if (Q[i] == 1)
        {
            Qf.push_back((range_start + i) * (range_start + i) - N);
            X.push_back((range_start + i));
        }
    }
    return {Qf, X};
}
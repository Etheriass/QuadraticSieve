#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <utility> 
#include "friables.hpp"
#include "../Eratosthene/eratosthene.hpp"
#include "../Legendre/legendre.hpp"

typedef unsigned long long ull;


std::pair<std::vector<ull>, std::vector<ull>> QBfriablesV2Long(const ull N, const size_t A, const std::vector<int> &primes)
{
    ull range_start = (ull)sqrt(N) + 1;
    std::vector<ull> Q(A), Qf, X;
    Qf.reserve(A); // Reserve space but do not initialize the elements
    X.reserve(A);
    // std::vector<ull> Qf(A);
    // std::vector<ull> X(A);

    for (size_t i = 0; i < A; i++){
        Q[i] = (range_start+i)*(range_start+i) - N;
    }

    int count = 0;
    for (size_t i = 1; i < primes.size(); i++)
    {
        int legendre_symbol = legendre_long(N, primes[i]);
        if (legendre_symbol == 0) // If N is a multiple of primes[i]
        {
            printf("%llu is a multiple of %d\n", N, primes[i]);
            break;
        }
        if (legendre_symbol == 1) // If N is a quadratic residue modulo primes[i]
        {
            int pk = primes[i];
            int j = 0;
            int a1 = -1;
            int a2 = -1;
            while (j < std::min<size_t>(pk, A)) // Find both index where Q[j] == 0 mod pk
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
            int ecart = a2 - a1;
            for (size_t k = a1; k < A - ecart; k += pk) // There is only 2 multiples of pk by interval of pk
            {
                while (Q[k] % pk == 0)
                {
                    Q[k] = Q[k] / pk;
                }
                while (Q[k + ecart] % pk == 0)
                {
                    Q[k + ecart] = Q[k + ecart] / pk;
                }
            }
        }
    }

    for (size_t i = 0; i < A; i++)
    {
        if (Q[i] == 1)
        {
            // Qf[count] = (range_start + i) * (range_start + i) - N;
            // X[count] = range_start + i;
            // count++;
            Qf.push_back((range_start + i)*(range_start + i) - N);
            X.push_back((range_start + i));
        }
    }

    // Qf.resize(count);
    // X.resize(count);
    return {Qf, X};
}
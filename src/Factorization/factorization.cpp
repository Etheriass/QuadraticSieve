#include <vector>
#include "factorization.hpp"

std::vector<int> factors_powers(__uint128_t a, const std::vector<int> &primes)
{
    std::vector<int> factors_powers(primes.size(), 0);
    for (size_t i = 0; i < primes.size(); i++)
    {
        while (a % (__uint128_t)primes[i] == 0)
        {
            a = a / (__uint128_t)primes[i];
            factors_powers[i]++;
        }
    }
    return factors_powers;
}


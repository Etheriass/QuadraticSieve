#include <vector>
#include "factorization.hpp"

std::vector<int> factors_powers_f2(unsigned long long a, const std::vector<int> &primes)
{
    std::vector<int> factors_powers(primes.size(), 0);
    for (size_t i = 0; i < primes.size(); i++)
    {
        while (a % (unsigned long long)primes[i] == 0)
        {
            a = a / (unsigned long long)primes[i];
            if (factors_powers[i] == 0)
                factors_powers[i] = 1;
            else
                factors_powers[i] = 0;
        }
    }
    return factors_powers;
}

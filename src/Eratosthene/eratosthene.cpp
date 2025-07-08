#include <vector>
#include "eratosthene.hpp"

std::vector<int> eratosthene_sieve(const int n)
{
    std::vector<bool> isPrime(n + 1, true); // Create a boolean array to mark prime numbers
    isPrime[0] = isPrime[1] = false;        // 0 and 1 are not primes

    for (int i = 2; i * i <= n; ++i)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }

    // Collect all primes into a vector
    std::vector<int> primes;
    for (int i = 2; i <= n; ++i)
    {
        if (isPrime[i])
            primes.push_back(i);
    }

    return primes;
}

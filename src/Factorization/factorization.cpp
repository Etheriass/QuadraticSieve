#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "factorization.hpp"

int *factorization(unsigned long long a, unsigned long long *primes, int sizePrimes)
{
    int *factors = (int *)calloc(sizePrimes, sizeof(int));
    if (factors == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < sizePrimes; i++)
    {
        if (a % primes[i] == 0)
        {
            while (a % primes[i] == 0)
            {
                a = a / primes[i];
                factors[i]++;
            }
        }
    }
    return factors;
}

std::vector<int> factorsPowersMod2(unsigned long long a, std::vector<int> primes)
{
    std::vector factorsPowers(primes.size(), 0);
    for (int i = 0; i < primes.size(); i++)
    {
        while (a % (unsigned long long)primes[i] == 0)
        {
            a = a / (unsigned long long)primes[i];
            if (factorsPowers[i] == 0)
            {
                factorsPowers[i] = 1;
            }
            else
            {
                factorsPowers[i] = 0;
            }
        }
    }
    return factorsPowers;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/Factorization/factorization.h"
#include "../src/Eratosthene/eratosthene.h"

int main()
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    unsigned long long a = 17595;

    int nbPrimes;
    unsigned long long *primes = eratostheneSieveLong(26, &nbPrimes);
    int *factors = factorization(a, primes, nbPrimes);
    printf("\n");
    printf("%lld factorization :\n", a);
    for (int i = 0; i < nbPrimes; i++)
    {
        printf("%lld : %d\n", primes[i], factors[i]);
    }
    int *factorsMod2 = factorizationMod2(a, primes, nbPrimes);
    printf("Mod 2 :\n");
    for (int i = 0; i < nbPrimes; i++)
    {
        printf("%lld : %d\n", primes[i], factorsMod2[i]);
    }
    free(primes);
    free(factors);
    free(factorsMod2);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
    return 0;
}

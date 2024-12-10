#include <stdio.h>
#include <stdlib.h>
#include "eratosthene.h"

int *eratostheneSieve(int n, int *resultSize)
{
    int *entiers = (int *)malloc(n * sizeof(int));
    if (entiers == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    entiers[0] = 2;
    int k = 1;

    for (int i = 3; i <= n; i += 2)
    {
        entiers[k++] = i;
    }

    int i = 0;
    while (entiers[i] * entiers[i] <= n)
    {
        for (int j = entiers[i] * entiers[i]; j <= n; j += 2 * entiers[i])
        {
            // If j is present in the array, remove it
            for (int m = 0; m < k; ++m)
            {
                if (entiers[m] == j)
                {
                    // Shift elements to fill the gap
                    for (int l = m; l < k - 1; ++l)
                    {
                        entiers[l] = entiers[l + 1];
                    }
                    --k;
                    break;
                }
            }
        }
        ++i;
    }

    // Resize the array to the actual number of primes found
    entiers = realloc(entiers, k * sizeof(int));
    if (entiers == NULL)
    {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }

    *resultSize = k;
    return entiers;
}


unsigned long long *eratostheneSieveLong(int n, int *resultSize)
{
    unsigned long long *entiers = malloc(((int)(n)) * sizeof(unsigned long long));
    if (entiers == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    entiers[0] = 2;
    int k = 1;

    for (int i = 3; i <= n; i += 2)
    {
        entiers[k++] = i;
    }

    int i = 0;
    while (entiers[i] * entiers[i] <= n)
    {
        for (int j = entiers[i] * entiers[i]; j <= n; j += 2 * entiers[i])
        {
            // If j is present in the array, remove it
            for (int m = 0; m < k; ++m)
            {
                if (entiers[m] == j)
                {
                    // Shift elements to fill the gap
                    for (int l = m; l < k - 1; ++l)
                    {
                        entiers[l] = entiers[l + 1];
                    }
                    --k;
                    break;
                }
            }
        }
        ++i;
    }

    // Resize the array to the actual number of primes found
    entiers = realloc(entiers, k * sizeof(unsigned long long));
    if (entiers == NULL)
    {
        fprintf(stderr, "Memory reallocation failed\n");
        exit(EXIT_FAILURE);
    }

    *resultSize = k;
    return entiers;
}

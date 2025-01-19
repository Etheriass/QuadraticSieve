#include <stdio.h>
#include <stdlib.h>
#include "eratosthene.hpp"
#include <vector>

std::vector<int> eratostheneSieve(int n) {
    if (n < 2) {
        return {};
    }

    // Create a boolean array to mark prime numbers
    std::vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false; // 0 and 1 are not primes

    for (int i = 2; i * i <= n; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // Collect all primes into a vector
    std::vector<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}


std::vector<unsigned long long> eratostheneSieveLong(int n) {
    if (n < 2) {
        return {};
    }

    // Create a boolean array to mark prime numbers
    std::vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false; // 0 and 1 are not primes

    for (int i = 2; i * i <= n; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    // Collect all primes into a vector
    std::vector<unsigned long long> primes;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}


// int *eratostheneSieve(int n, int *resultSize)
// {
//     int *entiers = (int *)malloc(n * sizeof(int));
//     if (entiers == NULL)
//     {
//         fprintf(stderr, "Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }

//     entiers[0] = 2;
//     int k = 1;

//     for (int i = 3; i <= n; i += 2)
//     {
//         entiers[k++] = i;
//     }

//     int i = 0;
//     while (entiers[i] * entiers[i] <= n)
//     {
//         for (int j = entiers[i] * entiers[i]; j <= n; j += 2 * entiers[i])
//         {
//             // If j is present in the array, remove it
//             for (int m = 0; m < k; ++m)
//             {
//                 if (entiers[m] == j)
//                 {
//                     // Shift elements to fill the gap
//                     for (int l = m; l < k - 1; ++l)
//                     {
//                         entiers[l] = entiers[l + 1];
//                     }
//                     --k;
//                     break;
//                 }
//             }
//         }
//         ++i;
//     }

//     // Resize the array to the actual number of primes found
//     entiers = (int *)realloc(entiers, k * sizeof(int));
//     if (entiers == NULL)
//     {
//         fprintf(stderr, "Memory reallocation failed\n");
//         exit(EXIT_FAILURE);
//     }

//     *resultSize = k;
//     return entiers;
// }


// unsigned long long *eratostheneSieveLong(int n, int *resultSize)
// {
//     unsigned long long *entiers = (unsigned long long *)malloc(((int)(n)) * sizeof(unsigned long long));
//     if (entiers == NULL)
//     {
//         fprintf(stderr, "Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }

//     entiers[0] = 2;
//     int k = 1;

//     for (int i = 3; i <= n; i += 2)
//     {
//         entiers[k++] = i;
//     }

//     int i = 0;
//     while (entiers[i] * entiers[i] <= n)
//     {
//         for (int j = entiers[i] * entiers[i]; j <= n; j += 2 * entiers[i])
//         {
//             // If j is present in the array, remove it
//             for (int m = 0; m < k; ++m)
//             {
//                 if (entiers[m] == j)
//                 {
//                     // Shift elements to fill the gap
//                     for (int l = m; l < k - 1; ++l)
//                     {
//                         entiers[l] = entiers[l + 1];
//                     }
//                     --k;
//                     break;
//                 }
//             }
//         }
//         ++i;
//     }

//     // Resize the array to the actual number of primes found
//     entiers = (unsigned long long *)realloc(entiers, k * sizeof(unsigned long long));
//     if (entiers == NULL)
//     {
//         fprintf(stderr, "Memory reallocation failed\n");
//         exit(EXIT_FAILURE);
//     }

//     *resultSize = k;
//     return entiers;
// }

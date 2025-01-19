#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "friables.hpp"
#include "../Eratosthene/eratosthene.hpp"
#include "../Legendre/legendre.hpp"

typedef unsigned long long ull;

/*
* Sieve of integers B-smooth
* -------------------------------------
* max : the maximum number to check
* B : the smoothness bound

* returns: an array where '1' represent the B-smooth numbers
*/
// int *Bfriables(int B, int max)
// {
//     int *friables = (int *)malloc((max - 1) * sizeof(int));
//     if (friables == NULL)
//     {
//         fprintf(stderr, "Memory allocation failed\n");
//         return NULL;
//     }

//     for (int i = 2; i <= max; i++)
//     {
//         friables[i] = i;
//     }

//     int nbPrimes;
//     int *primes = eratostheneSieve(B, &nbPrimes);

//     for (int i = 0; i < nbPrimes; ++i)
//     {
//         for (int p = primes[i]; p <= max; p = p * primes[i])
//         {
//             for (int j = p; j <= max; j += p)
//             {
//                 if (j == p)
//                     friables[j] = 1;
//                 else if ((friables[j] / primes[i]) % p != 0)
//                     friables[j] = friables[j] / p;
//             }
//         }
//     }
//     free(primes);
//     return friables;
// }

// int *BfriablesV2(int B, int max)
// {
//     int *friables = (int *)malloc((max - 1) * sizeof(int));
//     if (friables == NULL)
//     {
//         fprintf(stderr, "Memory allocation failed\n");
//         return NULL;
//     }

//     for (int i = 2; i <= max; i++)
//     {
//         friables[i] = i;
//     }

//     int nbPrimes;
//     int *primes = eratostheneSieve(B, &nbPrimes);

//     for (int i = 0; i < nbPrimes; ++i)
//     {
//         int p = primes[i];
//         for (int j = p; j <= max; j += p)
//         {
//             while (friables[j] % p == 0)
//             {
//                 friables[j] = friables[j] / p;
//             }
//         }
//     }
//     free(primes);
//     return friables;
// }

// int *QBfriables(int B, int N, int A, int *size)
// {
//     int min = (int)sqrt(N) + 1;
//     int max = sqrt(N) + A;
//     int sizeArray = max - min;
//     int *Q = (int *)malloc(sizeArray * sizeof(int));
//     int *QCopy = (int *)malloc(sizeArray * sizeof(int));
//     if (Q == NULL || QCopy == NULL)
//     {
//         fprintf(stderr, "Memory allocation failed\n");
//         return NULL;
//     }

//     for (int i = 0; i < sizeArray; i++)
//     {
//         int e = pow(min + i, 2) - N;
//         Q[i] = e;
//         QCopy[i] = e;
//     }

//     int nbPrimes;
//     int *primes = eratostheneSieve(B, &nbPrimes);

//     int count = 0;

//     // Case Q[i] is a multiple of 2
//     for (int i = 0; i < sizeArray; i++)
//     {
//         while (Q[i] % 2 == 0)
//         {
//             Q[i] = Q[i] / 2;
//         }
//     }
//     for (int i = 1; i < nbPrimes; i++)
//     {
//         if (Legendre(N, primes[i])) // If N is a quadratic residue modulo primes[i]
//         {
//             for (int pk = primes[i]; pk <= max; pk = pk * primes[i]) // For each power of primes[i]
//             {
//                 for (int j = 0; j < sizeArray; j++)
//                 {
//                     while (Q[j] % pk == 0)
//                     {
//                         Q[j] = Q[j] / pk;
//                     }
//                 }
//             }
//         }
//     }

//     int *Qf = (int *)malloc(sizeArray * sizeof(int));
//     if (Qf == NULL)
//     {
//         fprintf(stderr, "Memory allocation failed\n");
//         return NULL;
//     }

//     for (int i = 0; i < sizeArray; i++)
//     {
//         if (Q[i] == 1)
//         {
//             Qf[count] = QCopy[i];
//             count++;
//         }
//     }

//     Qf = realloc(Qf, count * sizeof(Qf[0]));
//     *size = count;

//     free(primes);
//     return Qf;
// }

// int *QBfriablesV2(int B, int N, int A, int *size)
// {
//     int min = (int)sqrt(N) + 1;
//     int max = sqrt(N) + A;
//     int sizeArray = max - min;
//     int *Q = (int *)malloc(sizeArray * sizeof(int));
//     int *Qf = (int *)malloc(sizeArray * sizeof(int));
//     if (Q == NULL || Qf == NULL)
//     {
//         fprintf(stderr, "Memory allocation failed\n");
//         return NULL;
//     }

//     // Build the array Q and divide every element by 2 until it's odd
//     int e;
//     for (int i = 0; i < sizeArray; i++)
//     {
//         e = pow(min + i, 2) - N;
//         while (e % 2 == 0)
//         {
//             e = e / 2;
//         }
//         Q[i] = e;
//     }

//     // Get the primes up to B
//     int nbPrimes;
//     int *primes = eratostheneSieve(B, &nbPrimes);
//     int count = 0;

//     // For each prime number
//     for (int i = 1; i < nbPrimes; i++)
//     {
//         int legendre = Legendre(N, primes[i]);
//         if (legendre == 0)
//         { // If N is a multiple of primes[i]
//             printf("%d is a multiple of %d\n", N, primes[i]);
//             break;
//         }
//         if (legendre == 1) // If N is a quadratic residue modulo primes[i]
//         {
//             int pk = primes[i];
//             int j = 0;
//             int a1 = -1;   // Index of the first multiple of pk
//             int a2;        // Index of the second multiple of pk
//             while (j < pk) // Find both index where Q[j] == 0 mod pk
//             {
//                 if (Q[j] % pk == 0)
//                 {
//                     if (a1 == -1)
//                     {
//                         a1 = j;
//                     }
//                     else
//                     {
//                         a2 = j;
//                         break;
//                     }
//                 }
//                 j++;
//             }
//             int ecart = a2 - a1;
//             for (int k = a1; k < sizeArray - ecart; k += pk) // There is only 2 multiples of pk by interval of pk
//             {
//                 while (Q[k] % pk == 0)
//                 {
//                     Q[k] = Q[k] / pk;
//                 }
//                 while (Q[k + ecart] % pk == 0)
//                 {
//                     Q[k + ecart] = Q[k + ecart] / pk;
//                 }
//             }
//         }
//     }

//     // Smooth numbers are the one that are equal to 1
//     for (int i = 0; i < sizeArray; i++)
//     {
//         if (Q[i] == 1)
//         {
//             Qf[count] = pow(min + i, 2) - N;
//             count++;
//         }
//     }

//     Qf = realloc(Qf, count * sizeof(Qf[0]));
//     *size = count;

//     free(primes);
//     return Qf;
// }

unsigned long long power(unsigned long long x, int y)
{
    unsigned long long res = 1;
    while (y > 0)
    {
        if (y & 1)
            res *= x;
        y >>= 1;
        x *= x;
    }
    return res;
}

unsigned long long *QBfriablesV2Long(int B, unsigned long long N, int A, int *size)
{
    // printf("N = %llu\n", N);
    ull min = (ull)sqrt(N) + 1;
    ull max = (ull)sqrt(N) + A;
    // printf("min = %llu, max = %llu\n", min, max);
    int sizeArray = max - min;
    unsigned long long *Q = (unsigned long long*)malloc(sizeArray * sizeof(unsigned long long));
    ull *Qf = (ull *)malloc(sizeArray * sizeof(ull));
    if (Q == NULL || Qf == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    ull e;
    for (int i = 0; i < sizeArray; i++)
    {
        e = power(min + i, 2) - N;
        while (e % 2 == 0) // Divide by 2 until e is odd to save time
        {
            e = e / 2;
        }
        Q[i] = e;
    }

    int count = 0;
    std::vector<unsigned long long> primes = eratostheneSieveLong(B);
    int nb_primes = primes.size();
    for (int i = 1; i < nb_primes; i++)
    {
        int legendre = LegendreLong(N, primes[i]);
        if (legendre == 0) // If N is a multiple of primes[i]
        {
            printf("%llu is a multiple of %llu\n", N, primes[i]);
            break;
        }
        if (legendre == 1) // If N is a quadratic residue modulo primes[i]
        {
            int pk = primes[i];
            int j = 0;
            int a1 = -1;
            int a2 = -1;
            while (j < pk) // Find both index where Q[j] == 0 mod pk
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
            for (int k = a1; k < sizeArray - ecart; k += pk) // There is only 2 multiples of pk by interval of pk
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

    for (int i = 0; i < sizeArray; i++)
    {
        if (Q[i] == 1)
        {
            Qf[count] = power(min + i, 2) - N;
            count++;
        }
    }

    Qf = (ull*)realloc(Qf, count * sizeof(Qf[0]));
    *size = count;
    
    free(Q);
    return Qf;
}
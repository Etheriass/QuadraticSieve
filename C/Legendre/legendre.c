#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "legendre.h"

/*
 * Legendre symbol
 * ---------------
 * m : the number to check
 * N : the prime number
 *
 * returns:
 * - 1 if m is a quadratic residue modulo N
 * - 0 if m is a multiple of N
 * - -1 if m is a non-quadratic residue modulo N
 */
int Legendre(int m, int N)
{
    if (N == 0 || (N % 2 == 0 && N != 2))
        fprintf(stderr, "N must be an odd prime number\n"),
            exit(EXIT_FAILURE);

    // Multiple de N
    if (m % N == 0)
        return 0;

    // Valeurs particulières
    if (m == 0)
        return 0;
    if (m == 1)
        return 1;

    // Cas pair
    if (m % 2 == 0)
        if (N % 8 == 1 || N % 8 == 7)
            return Legendre(m / 2, N);
        else
            return -Legendre(m / 2, N);
    else if (m > N) // Cas impair
        return Legendre(m % N, N);
    else if (m % 4 == 3 && N % 4 == 3)
        return -Legendre(N, m);
    else
        return Legendre(N, m);
}

int LegendreLong(unsigned long long int n, int p)
{
    if (p == 0 || (p % 2 == 0 && p != 2))
        fprintf(stderr, "p must be an odd prime number\n"),
            exit(EXIT_FAILURE);

    // Multiple de N
    if (n % p == 0)
        return 0;

    // Valeurs particulières
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;

    // Cas pair
    if (n % 2 == 0)
        if (p % 8 == 1 || p % 8 == 7)
            return Legendre(n / 2, p);
        else
            return -Legendre(n / 2, p);
    else if (n > p) // Cas impair
        return Legendre(n % p, p);
    else if (n % 4 == 3 && p % 4 == 3)
        return -Legendre(p, n);
    else
        return Legendre(p, n);
}
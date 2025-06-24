#include <stdexcept>
#include "legendre.hpp"

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
int legendre(int m, int N)
{
    if (N == 0 || (N % 2 == 0 && N != 2))
        throw std::invalid_argument("Legendre symbol: p must be an odd prime number");

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
            return legendre(m / 2, N);
        else
            return -legendre(m / 2, N);
    else if (m > N) // Cas impair
        return legendre(m % N, N);
    else if (m % 4 == 3 && N % 4 == 3)
        return -legendre(N, m);
    else
        return legendre(N, m);
}

int legendre_long(unsigned long long int n, int p)
{
    if (p == 0 || (p % 2 == 0 && p != 2))
        throw std::invalid_argument("Legendre symbol: p must be an odd prime number");

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
            return legendre_long(n / 2, p);
        else
            return -legendre_long(n / 2, p);
    else if (n > p) // Cas impair
        return legendre_long(n % p, p);
    else if (n % 4 == 3 && p % 4 == 3)
        return -legendre_long(p, n);
    else
        return legendre_long(p, n);
}
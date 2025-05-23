#ifndef LEGENDRE_H
#define LEGENDRE_H
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
int Legendre(int m, int N);

/*
 * Legendre symbol for unsigned long long int
 * ------------------------------------------
 * n : the number to check
 * p : the prime number
 *
 * returns:
 * - 1 if m is a quadratic residue modulo N
 * - 0 if m is a multiple of N
 * - -1 if m is a non-quadratic residue modulo N
 */
int LegendreLong(unsigned long long int n, int p);
#endif
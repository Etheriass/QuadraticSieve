#ifndef ERATOSTHENE_H
#define ERATOSTHENE_H


/*
 * Eratosthene Sieve
 * ---------------
 * n : bound
 * resultsize : pointer to get number of primes below n
 *
 * returns: An array of the primes less or equal to n
 */
int* eratostheneSieve(int n, int* resultSize);
// unsigned long long* eratostheneSieveLong(int n, int* resultSize);

#endif
#ifndef ERATOSTHENE_H
#define ERATOSTHENE_H
#include <vector>

/*
 * Eratosthene Sieve
 * ---------------
 * n : bound
 * resultsize : pointer to get number of primes below n
 *
 * returns: An array of the primes less or equal to n
 */
std::vector<int> eratostheneSieve(int n);
// int* eratostheneSieve(int n, int* resultSize);

std::vector<unsigned long long> eratostheneSieveLong(int n);
// unsigned long long* eratostheneSieveLong(int n, int* resultSize);

#endif
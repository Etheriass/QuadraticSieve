#ifndef ERATOSTHENE_H
#define ERATOSTHENE_H
#include <vector>

/*
 * Eratosthene Sieve
 * ---------------
 * n : bound
 * returns: An array of the primes less or equal to n
 */
std::vector<int> eratosthene_sieve(int n);
std::vector<unsigned long long> eratosthene_sieve_long(int n);

#endif
#ifndef FRIABLES_H
#define FRIABLES_H
#include <utility> 

/*
* Sieve of integers B-smooth
* -------------------------------------
* N: the number to factor
* A: the number of integers to sieve
* primes: the list of primes to use for the sieving

* returns: a pair of vectors:
* - the first vector contains the Q-B-Friable numbers
* - the second vector contains the corresponding X values
* -------------------------------------
*/
std::pair<std::vector<unsigned long long>, std::vector<unsigned long long>> QBfriablesV2Long(const unsigned long long N, const size_t A, const std::vector<int> &factor_base);

#endif
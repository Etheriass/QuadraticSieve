#ifndef FRIABLES_HPP
#define FRIABLES_HPP
#include <utility> 
#include <vector>

/*
* Sieve of integers B-smooth
* -------------------------------------
* N: the number to factor
* A: the number of integers to sieve
* factor_base: the list of primes to use for the sieving

* returns: a pair of vectors:
* - the first vector contains the Q-B-Friable numbers
* - the second vector contains the corresponding X values
* -------------------------------------
*/
std::pair<std::vector<__uint128_t>, std::vector<__uint128_t>> Q_B_friables_128(const __uint128_t N, const size_t A, const std::vector<int> &factor_base);

#endif
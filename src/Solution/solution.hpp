#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <vector>

__uint128_t a_computation(const std::vector<char> &w, const std::vector<__uint128_t> &X, __uint128_t N);
__uint128_t b_computation(const std::vector<std::vector<int>> &full_exponents, const std::vector<int> &factor_base, const std::vector<char> &w, __uint128_t N);

bool solution(__uint128_t N, __uint128_t a, __uint128_t b);


#endif
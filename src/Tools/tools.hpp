#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <string>
#include <chrono>
#include <vector>

__uint128_t sqrt_128(__uint128_t n);
__uint128_t gcd_128(__uint128_t a, __uint128_t b);
__uint128_t parse_u128(const std::string& s);

void print_header(__uint128_t N, int B);

using s = std::chrono::duration<double, std::ratio<1>>;
void print_timings(s coll, s era, s sieve, s mat, s proc, s cons, s kern, s sol, s total);

std::string to_str(__uint128_t v);

#endif
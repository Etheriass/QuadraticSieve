#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>

__uint128_t sqrt_128(__uint128_t n);
__uint128_t gcd_128(__uint128_t a, __uint128_t b);
__uint128_t parse_u128(const std::string& s);

using ms = std::chrono::duration<double, std::milli>;
using s = std::chrono::duration<double, std::ratio<1>>;

void print_header(__uint128_t N, int B);
bool solution(__uint128_t N, __uint128_t a, __uint128_t b, __uint128_t gcd1, __uint128_t gcd2);
void print_timings(s coll, s era, s sieve, s mat, s proc, s cons, s kern, s sol, s total);

std::string to_str(__uint128_t v);

#endif
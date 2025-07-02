#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>
using ms = std::chrono::duration<double, std::milli>;
using s = std::chrono::duration<double, std::ratio<1>>;

void print_header(unsigned long long N, int B);
void print_solution(unsigned long long N, __uint128_t a, __uint128_t b, unsigned long long gcd1, unsigned long long gcd2);
void print_timings(s coll, s era, s sieve, s mat, s proc, s cons, s kern, s sol, s total);

#endif
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>


// 128-bit square root using Newton's method
__uint128_t sqrt_128(__uint128_t n) {
    if (n == 0) return 0;
    if (n <= 1) return 1;
    
    __uint128_t x = n;
    __uint128_t y = (x + 1) / 2;
    
    while (y < x) {
        x = y;
        y = (x + n / x) / 2;
    }
    return x;
}

// 128-bit GCD using the Euclidean algorithm
__uint128_t gcd_128(__uint128_t a, __uint128_t b) {
    while (b != 0) {
        __uint128_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

__uint128_t parse_u128(const std::string& s) {
    __uint128_t x = 0;
    for (char c : s) {
        x = x * 10 + (c - '0');
    }
    return x;
}

auto to_str = [](__uint128_t v) {
    if (v == 0) return std::string("0");
    std::string s;
    while (v) {
        s.push_back(char('0' + (v % 10)));
        v /= 10;
    }
    std::reverse(s.begin(), s.end());
    return s;
};


void print_header(__uint128_t N, int B)
{
    std::cout
        << "=== Quadratic Sieve Factorization ===\n"
        << " N = " << to_str(N) << "\n"
        << " B = " << B << "\n\n";
}

void print_solution(__uint128_t N, __uint128_t a, __uint128_t b, __uint128_t gcd1, __uint128_t gcd2)
{
    std::cout << "Solution:\n"
              << "  a = " << to_str(a) << "\n"
              << "  b = " << to_str(b) << "\n"
              << "  gcd(a+b, N) = " << to_str(gcd1) << "\n"
              << "  gcd(b-a, N) = " << to_str(gcd2) << "\n\n";

    std::cout << "Factor found: {" << to_str(gcd1) << ", " << to_str(gcd2) << "}" << std::endl;
    if ((gcd1 == 1 && gcd2 == 1) || (gcd1 == 1 && gcd2 == N) || (gcd1 == N && gcd2 == 1) || (gcd1 == N && gcd2 == N))
    {
        std::cout << "FAIL: {" << to_str(gcd1) << ", " << to_str(gcd2) << "} are trivial factor of " << to_str(N) << std::endl;
    }
    else
    {
        if (N % gcd1 == 0 && gcd1 != 1 && gcd1 != N)
            std::cout << "SUCCESS: " << to_str(gcd1) << " is a non-trivial factor of " << to_str(N) << std::endl;
        if (N % gcd2 == 0 && gcd2 != 1 && gcd2 != N)
            std::cout << "SUCCESS: " << to_str(gcd2) << " is a non-trivial factor of " << to_str(N) << std::endl;
    }

}

using ms = std::chrono::duration<double, std::milli>;
using s = std::chrono::duration<double, std::ratio<1>>;

void print_timings(s coll, s era, s sieve, s mat, s proc, s cons, s kern, s sol, s total)
{
    auto pct = [&](s phase)
    { return phase.count() / total.count() * 100; };

    std::cout << "\n--- Timings (s) ------------- s -------- % --\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << std::setw(25) << std::left << "Collection phase"
              << std::setw(8) << coll.count()
              << std::setw(8) << pct(coll) << "%\n";
    std::cout << "  " << std::setw(23) << "Eratosthenes sieve"
              << std::setw(8) << era.count()
              << std::setw(8) << pct(era) << "%\n";
    std::cout << "  " << std::setw(23) << "Sieving"
              << std::setw(8) << sieve.count()
              << std::setw(8) << pct(ms(sieve)) << "%\n";
    std::cout << "  " << std::setw(23) << "Matrix filling"
              << std::setw(8) << mat.count()
              << std::setw(8) << pct(ms(mat)) << "%\n";
    std::cout << std::setw(25) << "Processing phase"
              << std::setw(8) << proc.count()
              << std::setw(8) << pct(proc) << "%\n";
    std::cout << "  " << std::setw(23) << "Matrix construction"
              << std::setw(8) << cons.count()
              << std::setw(8) << pct(cons) << "%\n";
    std::cout << "  " << std::setw(23) << "Kernel search"
              << std::setw(8) << kern.count()
              << std::setw(8) << pct(kern) << "%\n";
    std::cout << "  " << std::setw(23) << "Solution computation"
              << std::setw(8) << sol.count()
              << std::setw(8) << pct(sol) << "%\n";
    std::cout << std::setw(25) << "Total"
              << std::setw(8) << total.count() << "\n\n";
}
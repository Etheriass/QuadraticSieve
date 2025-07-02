#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>

using ms = std::chrono::duration<double, std::milli>;
using s = std::chrono::duration<double, std::ratio<1>>;

void print_header(unsigned long long N, int B)
{
    std::cout
        << "=== Quadratic Sieve Factorization ===\n"
        << " N = " << N << "\n"
        << " B = " << B << "\n\n";
}

void print_solution(unsigned long long N, __uint128_t a, __uint128_t b, unsigned long long gcd1, unsigned long long gcd2)
{
    auto to_str = [&](auto v)
    {
        if (v == 0)
            return std::string("0");
        std::string s;
        while (v)
        {
            s.push_back(char('0' + (v % 10)));
            v /= 10;
        }
        std::reverse(s.begin(), s.end());
        return s;
    };

    std::cout << "Solution:\n"
              << "  a = " << to_str(a) << "\n"
              << "  b = " << to_str(b) << "\n"
              << "  gcd(a+b, N) = " << gcd1 << "\n"
              << "  gcd(b-a, N) = " << gcd2 << "\n\n";

    std::cout << "Factor found: {" << gcd1 << ", " << gcd2 << "}" << std::endl;
    if ((gcd1 == 1 && gcd2 == 1) || (gcd1 == 1 && gcd2 == N) || (gcd1 == N && gcd2 == 1) || (gcd1 == N && gcd2 == N))
    {
        std::cout << "FAIL: {" << gcd1 << ", " << gcd2 << "} are trivial factor of " << N << std::endl;
    }
    else
    {
        if (N % gcd1 == 0 && gcd1 != 1 && gcd1 != N)
            std::cout << "SUCCESS: " << gcd1 << " is a non-trivial factor of " << N << std::endl;
        if (N % gcd2 == 0 && gcd2 != 1 && gcd2 != N)
            std::cout << "SUCCESS: " << gcd2 << " is a non-trivial factor of " << N << std::endl;
    }

}

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
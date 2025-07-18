#include <vector>
#include <iostream>
#include "../Tools/tools.hpp"

__uint128_t slow_mod_mul(__uint128_t a, __uint128_t b, __uint128_t mod)
{
    if (a == 0 || b == 0)
        return 0;
    a %= mod;
    b %= mod;

    __uint128_t result = 0;
    while (b > 0)
    {
        if (b & 1)
        {
            // Add a to result, handling overflow
            __uint128_t temp = mod - result;
            if (a >= temp)
                result = a - temp;
            else
                result += a;
        }

        // Double a, handling overflow
        __uint128_t temp = mod - a;
        if (a >= temp)
            a = a - temp;
        else
            a += a;

        b >>= 1;
    }
    return result;
}

__uint128_t safe_mod_mul(__uint128_t a, __uint128_t b, __uint128_t mod)
{
    __uint128_t prod;
    // GCC/Clang builtin to detect overflow:
    if (__builtin_mul_overflow(a, b, &prod))
        return slow_mod_mul(a, b, mod);
    else
        return prod % mod;
}

__uint128_t a_computation(const std::vector<char> &w, const std::vector<__uint128_t> &X, __uint128_t N)
{
    __uint128_t a = 1;
    for (int i = 0; i < w.size(); i++)
    {
        if (w[i] == 1)
            a = safe_mod_mul(a, X[i], N);
        // a = (a * X[i]) % N;
    }
    return a;
}

__uint128_t b_computation(const std::vector<std::vector<int>> &full_exponents, const std::vector<int> &factor_base, const std::vector<char> &w, __uint128_t N)
{
    __uint128_t b = 1;
    std::vector<int> exponents(factor_base.size(), 0);
    for (int i = 0; i < w.size(); i++)
    {
        if (w[i] == 1)
        {
            for (int j = 0; j < factor_base.size(); j++)
                exponents[j] += full_exponents[i][j];
        }
    }

    for (int j = 0; j < factor_base.size(); j++)
    {
        int half = exponents[j] / 2;
        while (half--)
            b = safe_mod_mul(b, factor_base[j], N);
        // b = (b * factor_base[j]) % N;
    }

    return b;
}

bool solution(__uint128_t N, __uint128_t a, __uint128_t b)
{
    __uint128_t gcd1 = b >= a ? gcd_128((b - a) % N, N) : gcd_128((a - b) % N, N);
    __uint128_t gcd2 = gcd_128((a + b) % N, N);
    
    std::cout << " Tentative solution:\n"
              << "  a = " << to_str(a) << "\n"
              << "  b = " << to_str(b) << "\n";

    b >= a ? std::cout << "  gcd(b-a, N) = " << to_str(gcd1) << "\n"
           : std::cout << "  gcd(a-b, N) = " << to_str(gcd1) << "\n";
    std::cout << "  gcd(a+b, N) = " << to_str(gcd2) << "\n\n";

    if ((gcd1 == 1 && gcd2 == 1) || (gcd1 == 1 && gcd2 == N) || (gcd1 == N && gcd2 == 1) || (gcd1 == N && gcd2 == N))
    {
        std::cout << " FAIL: {" << to_str(gcd1) << ", " << to_str(gcd2) << "} are trivial factor of " << to_str(N) << std::endl;
        std::cout << " Looking for another kernel vector\n"
                  << std::endl;
        return false;
    }
    else if (N % gcd1 == 0 && gcd1 != 1 && gcd1 != N)
    {
        std::cout << "SUCCESS: " << to_str(gcd1) << " is a non-trivial factor of " << to_str(N) << std::endl;
        return true;
    }
    else if (N % gcd2 == 0 && gcd2 != 1 && gcd2 != N)
    {
        std::cout << "SUCCESS: " << to_str(gcd2) << " is a non-trivial factor of " << to_str(N) << std::endl;
        return true;
    }
    else
    {
        std::cout << " FAIL: unknown" << std::endl;
        return false;
    }
}
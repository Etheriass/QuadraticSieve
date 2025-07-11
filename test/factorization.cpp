#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include "../src/Eratosthene/eratosthene.hpp"
#include "../src/Factorization/factorization.hpp"

TEST(FactorizationTest, EmptyPrimes) {
    std::vector<int> primes = eratosthene_sieve(1);
    std::vector<int> factors = factors_powers(1, primes);
    std::vector<int> expected = {};
    EXPECT_EQ(factors, expected);
}

TEST(FactorizationTest, SmallInteger) {
    std::vector<int> primes = eratosthene_sieve(8);
    std::vector<int> factors = factors_powers(21, primes);
    std::vector<int> expected = { 0, 1, 0, 1 }; // 3 and 7
    EXPECT_EQ(factors, expected);
}


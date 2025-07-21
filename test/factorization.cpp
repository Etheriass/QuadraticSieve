#include <gtest/gtest.h>
#include <vector>
#include "../src/Eratosthene/eratosthene.hpp"
#include "../src/Factorization/factorization.hpp"

TEST(FactorizationTest, FactorizeOne) {
    std::vector<int> primes = eratosthene_sieve(10);
    std::vector<int> factors = factors_powers(1, primes);
    std::vector<int> expected = {0, 0, 0, 0};
    EXPECT_EQ(factors, expected);
}

TEST(FactorizationTest, FactorizePrime) {
    std::vector<int> primes = eratosthene_sieve(10);
    std::vector<int> factors = factors_powers(7, primes);
    std::vector<int> expected = {0, 0, 0, 1}; // 7^1
    EXPECT_EQ(factors, expected);
}

TEST(FactorizationTest, FactorizeComposite) {
    std::vector<int> primes = eratosthene_sieve(10);
    std::vector<int> factors = factors_powers(12, primes);
    std::vector<int> expected = {2, 1, 0, 0}; // 2^2 * 3^1
    EXPECT_EQ(factors, expected);
}

TEST(FactorizationTest, FactorizeWithLargePrime) {
    std::vector<int> primes = eratosthene_sieve(50);
    std::vector<int> factors = factors_powers(49, primes);
    std::vector<int> expected = { 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 7^2
    EXPECT_EQ(factors, expected);
}

// Unlikely
// TEST(FactorizationTest, FactorizeZero) {
//     std::vector<int> primes = eratosthene_sieve(10);
//     std::vector<int> factors = factors_powers(0, primes);
//     std::vector<int> expected = {};
//     EXPECT_EQ(factors, expected);
// }

TEST(FactorizationTest, FactorizeLargeNumber) {
    std::vector<int> primes = eratosthene_sieve(100);
    std::vector<int> factors = factors_powers(2*2*3*5*7*11, primes);
    std::vector<int> expected = { 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // 2^2 * 3^1 * 5^1 * 7^1 * 11^1
    EXPECT_EQ(factors, expected);
}

TEST(FactorizationTest, FactorizeWithInsufficientPrimes) {
    std::vector<int> primes = eratosthene_sieve(3); // primes: 2, 3
    std::vector<int> factors = factors_powers(30, primes);
    std::vector<int> expected = {1, 1}; // Only 2^1 * 3^1, can't factor 5
    EXPECT_EQ(factors, expected);
}
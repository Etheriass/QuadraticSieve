#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include "../src/Eratosthene/eratosthene.hpp"

TEST(EratostheneTest, EmptyPrimes) {
    std::vector<int> primes = eratostheneSieve(1);
    std::vector<int> expected = {};
    EXPECT_EQ(primes, expected);
}

TEST(EratostheneTest, SmallPrimes) {
    std::vector<int> primes = eratostheneSieve(10);
    std::vector<int> expected = {2, 3, 5, 7};
    EXPECT_EQ(primes, expected);
}

TEST(EratostheneTest, LargePrimes) {
    std::vector<int> primes = eratostheneSieve(50);
    std::vector<int> expected = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    EXPECT_EQ(primes, expected);
}

#include <gtest/gtest.h>
#include <vector>
#include "../src/Legendre/legendre.hpp"


// -- Exception cases ------------------------------------------------

TEST(Legendre128, ThrowsOnPZero) {
    EXPECT_THROW(legendre_128(1, 0), std::invalid_argument);
}

TEST(Legendre128, ThrowsOnEvenPNot2) {
    EXPECT_THROW(legendre_128(1, 4), std::invalid_argument);
}

// -- Zero and trivial cases -----------------------------------------

TEST(Legendre128, NIsZeroReturns0) {
    EXPECT_EQ(legendre_128(0, 3), 0);
}

TEST(Legendre128, NDivisibleByPReturns0) {
    EXPECT_EQ(legendre_128(9, 3), 0);
}

TEST(Legendre128, NIsOneReturns1) {
    EXPECT_EQ(legendre_128(1, 7), 1);
}

// -- Even N branch: Legendre(2,p) = ±1 depending on p mod 8 --------------

TEST(Legendre128, TwoEvenBranchPmod8Equals1) {
    // p = 17 ≡ 1 mod 8 → Legendre(2,17) = +1
    EXPECT_EQ(legendre_128(2, 17), 1);
}

TEST(Legendre128, TwoEvenBranchPmod8Equals3) {
    // p = 3 ≡ 3 mod 8 → Legendre(2,3) = −1
    EXPECT_EQ(legendre_128(2, 3), -1);
}

TEST(Legendre128, TwoEvenBranchPmod8Equals5) {
    // p = 5 ≡ 5 mod 8 → Legendre(2,5) = −1
    EXPECT_EQ(legendre_128(2, 5), -1);
}

TEST(Legendre128, TwoEvenBranchPmod8Equals7) {
    // p = 7 ≡ 7 mod 8 → Legendre(2,7) = +1
    EXPECT_EQ(legendre_128(2, 7), 1);
}

// -- Reduction mod p (n > p) -----------------------------------------

TEST(Legendre128, ReductionModPForOddN) {
    // 5 > 3, odd → reduces to legendre_128(5%3 = 2, 3) = −1
    EXPECT_EQ(legendre_128(5, 3), -1);
}

// -- Quadratic reciprocity branch (both ≡3 mod 4) ---------------------

TEST(Legendre128, QuadraticReciprocityNegativeSwap) {
    // n = 3 ≡3 mod4, p = 7 ≡3 mod4 → returns −legendre_128(7,3)
    // legendre_128(7,3) → legendre_128(1,3) = +1, so overall −1
    EXPECT_EQ(legendre_128(3, 7), -1);
}

// -- Fallback swap branch (both not ≡3 mod4, odd and n<p) -------------

TEST(Legendre128, SimpleSwapWithoutSign) {
    // n = 3, p = 5: neither both ≡3 mod4, so returns legendre_128(5,3)
    // which is legendre_128(2,3) = −1
    EXPECT_EQ(legendre_128(3, 5), -1);
}

// -- Special case: p = 2 ----------------------------------------------

TEST(Legendre128, PEquals2IsAllowed) {
    // p=2 is allowed by your code, e.g. legendre_128(3,2) → +1
    EXPECT_EQ(legendre_128(3, 2), 1);
}
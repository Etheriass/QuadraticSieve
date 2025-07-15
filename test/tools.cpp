#include <gtest/gtest.h>
#include "../src/Tools/tools.hpp"
#include "../src/Tools/matrix.hpp"
#include "../src/Tools/vectors.hpp"


// --- sqrt_128 tests ---
TEST(Sqrt128Test, ZeroAndOne) {
    EXPECT_EQ(sqrt_128((__uint128_t)0), (__uint128_t)0);
    EXPECT_EQ(sqrt_128((__uint128_t)1), (__uint128_t)1);
}

TEST(Sqrt128Test, PerfectSquare) {
    EXPECT_EQ(sqrt_128((__uint128_t)25), (__uint128_t)5);
    EXPECT_EQ(sqrt_128((__uint128_t)144), (__uint128_t)12);
}

TEST(Sqrt128Test, NonPerfect) {
    // floor of sqrt(26) is 5
    EXPECT_EQ(sqrt_128((__uint128_t)26), (__uint128_t)5);
    // floor of sqrt(15) is 3
    EXPECT_EQ(sqrt_128((__uint128_t)15), (__uint128_t)3);
}

TEST(Sqrt128Test, LargeValue) {
    // sqrt(10^18) = 10^9
    __uint128_t n = (__uint128_t)1000000000000000000ULL;
    EXPECT_EQ(sqrt_128(n), (__uint128_t)1000000000ULL);
}

// --- gcd_128 tests ---
TEST(Gcd128Test, BasicCases) {
    EXPECT_EQ(gcd_128((__uint128_t)54, (__uint128_t)24), (__uint128_t)6);
    EXPECT_EQ(gcd_128((__uint128_t)24, (__uint128_t)54), (__uint128_t)6);
}

TEST(Gcd128Test, ZeroCases) {
    EXPECT_EQ(gcd_128((__uint128_t)0, (__uint128_t)5), (__uint128_t)5);
    EXPECT_EQ(gcd_128((__uint128_t)5, (__uint128_t)0), (__uint128_t)5);
    EXPECT_EQ(gcd_128((__uint128_t)0, (__uint128_t)0), (__uint128_t)0);
}

// --- parse_u128 and to_str tests ---
TEST(ParseU128Test, RoundTripSmall) {
    std::string s = "12345678901234567890";
    __uint128_t x = parse_u128(s);
    EXPECT_EQ(to_str(x), s);
}

TEST(ParseU128Test, Zero) {
    __uint128_t x = parse_u128("0");
    EXPECT_EQ(x, (__uint128_t)0);
    EXPECT_EQ(to_str(x), "0");
}

TEST(ParseU128Test, LargeString) {
    // 2^64 = 18446744073709551616
    std::string s = "18446744073709551616";
    __uint128_t x = parse_u128(s);
    EXPECT_EQ(to_str(x), s);
}

TEST(ParseU128Test, VeryLargeString) {
    // 2^128 = 340282366920938463463374607431768211455
    std::string s = "340282366920938463463374607431768211455";
    __uint128_t x = parse_u128(s);
    EXPECT_EQ(to_str(x), s);
}

TEST(ParseU128Test, TooLargeString) {
    // 2^128 = 340282366920938463463374607431768211455
    std::string s = "340282366920938463463374607431768211456";
    EXPECT_THROW(parse_u128(s), std::out_of_range);
}

TEST(ParseU128Test, NotNUmberString) {
    std::string s = "number";
    EXPECT_THROW(parse_u128(s), std::invalid_argument);
}


// Helper to compare integer vectors
void expect_vec_eq(const std::vector<int>& a, const std::vector<int>& b) {
    ASSERT_EQ(a.size(), b.size()) << "Vector sizes differ";
    for (size_t i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]) << "at index " << i;
    }
}

// --- transpose tests ---
TEST(TransposeTest, Rectangular2x3) {
    std::vector<int> A = {1,2,3,4,5,6}; // 2 rows, 3 cols
    std::vector<int> expected = {1,4,2,5,3,6}; // 3 rows, 2 cols (flattened)
    auto T = transpose(A, 2, 3);
    expect_vec_eq(T, expected);
}

// --- sum_vec tests ---
TEST(SumVecTest, NonEmpty) {
    std::vector<int> v = {1,2,3, -1};
    EXPECT_EQ(sum_vec(v), 5);
}

TEST(SumVecTest, Empty) {
    std::vector<int> v;
    EXPECT_EQ(sum_vec(v), 0);
}

// --- vec_add tests ---
TEST(VecAddTest, SameSize) {
    std::vector<int> u = {1,2,3};
    std::vector<int> v = {4,5,6};
    std::vector<int> expected = {5,7,9};
    expect_vec_eq(vec_add(u,v), expected);
}

TEST(VecAddTest, MismatchThrows) {
    std::vector<int> u = {1,2};
    std::vector<int> v = {1,2,3};
    EXPECT_THROW(vec_add(u,v), std::invalid_argument);
}

// --- vec_add_f2 tests ---
TEST(VecAddF2Test, Mod2) {
    std::vector<int> u = {1,0,1};
    std::vector<int> v = {1,1,0};
    // (1+1)%2=0, (0+1)%2=1, (1+0)%2=1
    std::vector<int> expected = {0,1,1};
    expect_vec_eq(vec_add_f2(u,v), expected);
}

TEST(VecAddF2Test, MismatchThrows) {
    std::vector<int> u = {1,2};
    std::vector<int> v = {3};
    EXPECT_THROW(vec_add_f2(u,v), std::invalid_argument);
}

// --- print_matrix tests ---
TEST(PrintMatrixTest, CapturesOutput) {
    std::vector<int> A = {1,2,3,4,5,6}; // 2x3
    std::string expected = "1 2 3 \n4 5 6 \n";
    testing::internal::CaptureStdout();
    print_matrix(A, 2, 3);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, expected);
}

// --- print_col_vec tests ---
TEST(PrintColVecTest, CapturesOutput) {
    std::vector<int> u = {7,8,9};
    std::string expected = "7\n8\n9\n";
    testing::internal::CaptureStdout();
    print_col_vec(u);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, expected);
}

// --- print_row_vec tests ---
TEST(PrintRowVecTest, CapturesOutput) {
    std::vector<int> u = {4,5,6};
    std::string expected = "[4 5 6 ]\n";
    testing::internal::CaptureStdout();
    print_row_vec(u);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_EQ(out, expected);
}

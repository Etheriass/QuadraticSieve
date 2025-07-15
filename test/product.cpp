#include <gtest/gtest.h>
#include <ctime>
#include "../src/Product/product.hpp"
#include "../src/Tools/tools.hpp"


// Helper to compare two integer vectors
void expect_vec_eq(const std::vector<int>& a, const std::vector<int>& b) {
    ASSERT_EQ(a.size(), b.size());
    for (size_t i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]) << "at index " << i;
    }
}

// --- dot_product_f2 tests ---
TEST(DotProductF2Test, BasicEvenSum) {
    std::vector<int> a = {1, 0, 1, 0};
    std::vector<int> b = {1, 1, 0, 0};
    // dot = 1*1 + 0*1 + 1*0 + 0*0 = 1 => 1 % 2 == 1
    EXPECT_EQ(dot_product_f2(a, b), 1);
}

TEST(DotProductF2Test, ZeroResult) {
    std::vector<int> a = {1, 1};
    std::vector<int> b = {1, 1};
    // dot = 1+1 = 2 => 2 % 2 == 0
    EXPECT_EQ(dot_product_f2(a, b), 0);
}

TEST(DotProductF2Test, SizeMismatchThrows) {
    std::vector<int> a = {1,2,3};
    std::vector<int> b = {1,0};
    EXPECT_THROW(dot_product_f2(a, b), std::invalid_argument);
}

// --- mat_vect_product_f2 tests ---
TEST(MatVectProductF2Test, Simple3x3) {
    // A is 3x3 identity matrix mod2, b = [1,1,0]
    std::vector<int> A = {
        1,0,0,
        0,1,0,
        0,0,1
    };
    std::vector<int> b = {1,1,0};
    std::vector<int> expected = {1,1,0};
    expect_vec_eq(mat_vect_product_f2(A, b), expected);
}

TEST(MatVectProductF2Test, Mod2Xor) {
    // A row [1,1,1] dot b = [1,1,1] using XOR = 1^1^1 = 1
    std::vector<int> A = {1,1,1};
    std::vector<int> b = {1,1,1};
    std::vector<int> expected = {1};
    expect_vec_eq(mat_vect_product_f2(A, b), expected);
}

TEST(MatVectProductF2Test, DimensionMismatchThrows) {
    std::vector<int> A = {1,2,3,4}; // size 4
    std::vector<int> b = {1,0,1};    // size 3, 4 % 3 != 0
    EXPECT_THROW(mat_vect_product_f2(A, b), std::invalid_argument);
}

// --- mat_product_f2 tests ---
TEST(MatProductF2Test, RectangularMultiply) {
    // A is 2x3, B is 3x2, result is 2x2
    std::vector<int> A = {
        1,0,1,
        0,1,1
    };
    std::vector<int> B = {
        1,1,
        0,1,
        1,0
    };
    // Compute mod2 XOR:
    // C[0,0] = 1&1 ^ 0&0 ^ 1&1 = 1^0^1 = 0
    // C[0,1] = 1&1 ^ 0&1 ^ 1&0 = 1^0^0 = 1
    // C[1,0] = 0&1 ^ 1&0 ^ 1&1 = 0^0^1 = 1
    // C[1,1] = 0&1 ^ 1&1 ^ 1&0 = 0^1^0 = 1
    std::vector<int> expected = {
        0,1,
        1,1
    };
    expect_vec_eq(mat_product_f2(A, B, 2, 3), expected);
}

// --- square_mat_product tests ---
TEST(SquareMatProductTest, Simple2x2) {
    std::vector<int> A = {1,2,3,4};
    std::vector<int> B = {2,0,1,2};
    // A*B = [1*2+2*1, 1*0+2*2; 3*2+4*1, 3*0+4*2]
    //      = [2+2, 0+4; 6+4, 0+8] = [4,4;10,8]
    std::vector<int> expected = {4,4,10,8};
    expect_vec_eq(square_mat_product(A, B, 2), expected);
}

TEST(SquareMatProductTest, OmpMatchesPlain) {
    std::vector<int> A = {1,0,1,0};
    std::vector<int> B = {0,1,0,1};
    auto plain = square_mat_product(A, B, 2);
    auto omp   = square_mat_product_omp(A, B, 2);
    expect_vec_eq(omp, plain);
}

// --- square_mat_product_omp_reorder tests ---
TEST(SquareMatProductReorderTest, MatchesPlainReorder) {
    // random 3x3 example
    std::vector<int> A = {
        1,2,3,
        4,5,6,
        7,8,9
    };
    std::vector<int> B = {
        9,8,7,
        6,5,4,
        3,2,1
    };
    auto plain   = square_mat_product(A, B, 3);
    auto reorder = square_mat_product_omp_reorder(A, B, 3);
    expect_vec_eq(reorder, plain);
}


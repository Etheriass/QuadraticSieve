#include <gtest/gtest.h>
#include "../src/Product/product.hpp"
#include "../src/Wiedemann/wiedemann.hpp"

std::vector<std::vector<char>> krylov_subspace(const std::vector<char>& A,
                                              const std::vector<char>& v,
                                              int d);
void set_u_v(std::vector<char>& u, std::vector<char>& v);
std::vector<char> berlekamp_massey(std::vector<char> s);

// Helper to compare two integer vectors
void expect_vec_eq(const std::vector<char>& a, const std::vector<char>& b) {
    ASSERT_EQ(a.size(), b.size());
    for (size_t i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]) << "at index " << i;
    }
}

// --- krylov_subspace tests ---
TEST(KrylovSubspaceTest, IdentityKeepsVector) {
    int n = 3;
    // Build 3x3 identity matrix over F2
    std::vector<char> I(n * n, 0);
    for (int i = 0; i < n; ++i) I[i*n + i] = 1;
    std::vector<char> v = {1, 0, 1};
    int d = 4;
    auto K = krylov_subspace(I, v, d);
    ASSERT_EQ(K.size(), d);
    for (int i = 0; i < d; ++i) {
        expect_vec_eq(K[i], v);
    }
}

// --- set_u_v tests ---
TEST(SetUVTest, OrthogonalAndBinary) {
    int n = 10;
    std::vector<char> u(n), v(n);
    set_u_v(u, v);
    // Check sizes
    ASSERT_EQ(u.size(), n);
    ASSERT_EQ(v.size(), n);
    // Check entries are 0 or 1
    for (int i = 0; i < n; ++i) {
        EXPECT_TRUE(u[i] == 0 || u[i] == 1);
        EXPECT_TRUE(v[i] == 0 || v[i] == 1);
    }
    // Check orthogonality in F2
    EXPECT_EQ(dot_product_f2(u, v), 0);
}

// --- berlekamp_massey tests ---
TEST(BerlekampMasseyTest, AlternatingSequence) {
    // s = 1,0,1,0,1,0,... minimal recurrence: s[n] = s[n-2]
    std::vector<char> s = {1,0,1,0,1,0};
    auto C = berlekamp_massey(s);
    // Expect C(x) = 1 + 0*x + 1*x^2 → vector {1,0,1}
    std::vector<char> expected = {1, 0, 1};
    expect_vec_eq(C, expected);
}

TEST(BerlekampMasseyTest, ConstantOnesSequence) {
    std::vector<char> s = {1,1,1,1,1};
    auto C = berlekamp_massey(s);
    // For constant 1's: recurrence s[n] = s[n-1] gives C = {1,1}
    std::vector<char> expected = {1,1};
    expect_vec_eq(C, expected);
}

TEST(BerlekampMasseyTest, ZeroSequence) {
    std::vector<char> s(5, 0);
    auto C = berlekamp_massey(s);
    // All zeros: trivial polynomial C = {1}
    std::vector<char> expected = {1};
    expect_vec_eq(C, expected);
}

// --- wiedemann tests ---
TEST(WiedemannTest, IdentityMatrixThrows) {
    int n = 3;
    // Build n x n identity matrix over F2
    std::vector<char> I(n * n, 0);
    for (int i = 0; i < n; ++i) I[i*n + i] = 1;
    // On identity, only trivial nullspace => should fail
    EXPECT_THROW(wiedemann(I, n, 10), std::runtime_error);
}

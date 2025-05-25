#include <gtest/gtest.h>
#include <ctime>
#include "../src/Product/product.hpp"
#include "../src/Tools/tools.hpp"

TEST(ProductTest, SquareMatProduct) {
    int n = 4;
    int** A = allocate_square_matrix(n, 1);
    int** B = allocate_square_matrix(n, 1);

    int** result = square_mat_product(A, B, n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            EXPECT_EQ(result[i][j], n);

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(result, n);
}

TEST(ProductTest, Mat4x4Product) {
    int n = 4;
    int** A = allocate_square_matrix(n, 1);
    int** B = allocate_square_matrix(n, 1);

    int** result = mat_4x4_product(A, B);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            EXPECT_EQ(result[i][j], n);

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(result, n);
}

TEST(ProductTest, Mat4x4ProductAlphaTensorZ2Z) {
    int n = 4;
    int** A = allocate_square_matrix(n, 1);
    int** B = allocate_square_matrix(n, 1);

    int** result = mat_4x4_product_alphatensor_Z2Z(A, B);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            EXPECT_EQ(result[i][j] % 2, n % 2);

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(result, n);
}

TEST(ProductTest, PerformanceComparison) {
    int n = 4;
    int** A = allocate_square_matrix(n, 1);
    int** B = allocate_square_matrix(n, 1);

    clock_t start, end;
    double time1, time2, time3;

    start = clock();
    int** s = square_mat_product(A, B, n);
    end = clock();
    time1 = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    int** t = mat_4x4_product(A, B);
    end = clock();
    time2 = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    int** v = mat_4x4_product_alphatensor_Z2Z(A, B);
    end = clock();
    time3 = ((double)(end - start)) / CLOCKS_PER_SEC;

    std::cout << "square_mat_product time: " << time1 << "s\n";
    std::cout << "mat_4x4_product time: " << time2 << "s\n";
    std::cout << "mat_4x4_product_alphatensor_Z2Z time: " << time3 << "s\n";

    EXPECT_TRUE(is_matrix_equal(s, t, n));
    EXPECT_TRUE(is_matrix_equal_in_Z2(s, v, n));

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(s, n);
    free_matrix(t, n);
    free_matrix(v, n);
}

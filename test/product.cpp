#define BOOST_TEST_MODULE ProductTest
#include <boost/test/included/unit_test.hpp>
#include <ctime>
#include "../src/Product/product.hpp"
#include "../src/Tools/tools.hpp"


BOOST_AUTO_TEST_CASE(test_square_mat_product) {
    int n = 4;
    int** A = allocate_square_matrix(n, 1);
    int** B = allocate_square_matrix(n, 1);

    int** result = square_mat_product(A, B, n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            BOOST_CHECK(result[i][j] == n);

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(result, n);
}

BOOST_AUTO_TEST_CASE(test_mat_4x4_product) {
    int n = 4;
    int** A = allocate_square_matrix(n, 1);
    int** B = allocate_square_matrix(n, 1);

    int** result = mat_4x4_product(A, B);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            BOOST_CHECK(result[i][j] == n);

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(result, n);
}

BOOST_AUTO_TEST_CASE(test_mat_4x4_product_alphatensor_Z2Z) {
    int n = 4;
    int** A = allocate_square_matrix(n, 1);
    int** B = allocate_square_matrix(n, 1);

    int** result = mat_4x4_product_alphatensor_Z2Z(A, B);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            BOOST_CHECK(result[i][j] % 2 == n % 2);

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(result, n);
}

BOOST_AUTO_TEST_CASE(test_performance_comparison) {
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

    BOOST_TEST_MESSAGE("square_mat_product time: " << time1 << "s");
    BOOST_TEST_MESSAGE("mat_4x4_product time: " << time2 << "s");
    BOOST_TEST_MESSAGE("mat_4x4_product_alphatensor_Z2Z time: " << time3 << "s");

    BOOST_CHECK(is_matrix_equal(s, t, n));
    BOOST_CHECK(is_matrix_equal_in_Z2(s, v, n));

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(s, n);
    free_matrix(t, n);
    free_matrix(v, n);
}
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "product.hpp"

#ifdef USE_OPENMP
#include <omp.h>
#endif

int dot_product(const std::vector<int> &a, const std::vector<int> &b)
{
    if (a.size() != b.size())
        throw std::invalid_argument("Dot product: vectors should have the same size");
    int res = 0;
    for (size_t i = 0; i < a.size(); i++)
        res += a[i] * b[i];
    return res;
}

int dot_product_f2(const std::vector<int> &a, const std::vector<int> &b)
{
    if (a.size() != b.size())
        throw std::invalid_argument("Dot product: vectors should have the same size");
    int res = 0;
    for (size_t i = 0; i < a.size(); i++)
        res += a[i] * b[i];
    res = res % 2;
    return res;
}

std::vector<int> mat_vect_product(const std::vector<int> &A, const std::vector<int> &b)
{
    int n = b.size();
    if (A.size() % n != 0)
        throw std::invalid_argument("Matrix-vector product: wrong dimensions");
    std::vector<int> res(A.size() / n);
    int r;
    for (int i = 0; i < A.size() / n; i++)
    {
        r = 0;
        for (int j = 0; j < n; j++)
            r += A[i * n + j] * b[j];
        res[i] = r;
    }
    return res;
}

std::vector<int> mat_vect_product_f2(const std::vector<int> &A, const std::vector<int> &b)
{
    int n = b.size();
    if (A.size() % n != 0)
        throw std::invalid_argument("Matrix-vector product: wrong dimensions");
    std::vector<int> res(A.size() / n);
    int r;
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
    for (int i = 0; i < A.size() / n; i++)
    {
        r = 0;
        for (int j = 0; j < n; j++)
        {
            // r += A[i*n + j] * b[j];
            r ^= (A[i * n + j] & b[j]);
        }
        res[i] = r;
    }
    return res;
}

std::vector<int> mat_product_f2(const std::vector<int> &A, const std::vector<int> &B, int n, int m)
{
    std::vector<int> M(n * n, 0);

    // Product
    int res = 0;
#ifdef USE_OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res = 0;
            for (int k = 0; k < m; k++)
            {
                // res += (A[i * m + k] * B[k * n + j]) % 2;
                res ^= (A[i * m + k] & B[k * n + j]);
            }
            M[i * n + j] = res;
        }
    }
    return M;
}

std::vector<int> square_mat_product_cpp(std::vector<int> A, std::vector<int> B, int n)
{

    std::vector<int> M(n * n, 0); // Should be faster withou init to 0 but somehow it look faster with it (maybe compiler optimizations)

    // Product
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res = 0;
            for (int k = 0; k < n; k++)
            {
                res += A[i * n + k] * B[k * n + j];
            }
            M[i * n + j] = res;
        }
    }
    return M;
}

std::vector<int> square_mat_product_cpp_parra(std::vector<int> A, std::vector<int> B, int n)
{

    std::vector<int> M(n * n, 0); // Should be faster withou init to 0 but somehow it look faster with it (maybe compiler optimizations)

    // Product
    int res = 0;
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res = 0;
            for (int k = 0; k < n; k++)
            {
                res += A[i * n + k] * B[k * n + j];
            }
            M[i * n + j] = res;
        }
    }
    return M;
}

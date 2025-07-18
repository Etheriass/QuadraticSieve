#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "product.hpp"

#ifdef USE_OPENMP
#include <omp.h>
#endif

char dot_product_f2(const std::vector<char> &a, const std::vector<char> &b)
{
    if (a.size() != b.size())
        throw std::invalid_argument("Dot product: vectors should have the same size");
    int res = 0;
    for (size_t i = 0; i < a.size(); i++)
        res += a[i] * b[i];
    res = res % 2;
    return res;
}

std::vector<char> mat_vect_product_f2(const std::vector<char> &A, const std::vector<char> &b)
{
    int n = b.size();
    if (A.size() % n != 0)
        throw std::invalid_argument("Matrix-vector product: wrong dimensions");
    std::vector<char> res(A.size() / n);
    char r;
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

std::vector<char> mat_vect_product_f2_enhanced(const std::vector<char> &A, const std::vector<char> &b)
{
    int n = b.size();
    int rows = A.size() / n;
    std::vector<char> res(rows);

    #pragma omp parallel for
    for (int i = 0; i < rows; i++)
    {
        char r = 0;
        for (int j = 0; j < n; j++)
        {
            // r += A[i*n + j] * b[j];
            r ^= (A[i * n + j] & b[j]);
        }
        res[i] = r;
    }
    return res;
}

std::vector<char> mat_product_f2(const std::vector<char> &A, const std::vector<char> &B, int n, int m)
{
    std::vector<char> M(n * n, 0);

    char res = 0;
#ifdef USE_OPENMP
#pragma omp parallel for
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

std::vector<char> mat_product_f2_reorder(const std::vector<char> &A, const std::vector<char> &B, int n)
{
    std::vector<char> M(n * n);

#pragma omp parallel for
    for (int i = 0; i < n; ++i)
    {
        char *Mi = M.data() + i * n;
        const char *Ai = A.data() + i * n;

        // zero row i
        for (int j = 0; j < n; ++j)
            Mi[j] = 0;

        // accumulate in k-outer, j-inner order
        for (int k = 0; k < n; ++k)
        {
            char a = Ai[k];
            const char *Bk = B.data() + k * n;
            for (int j = 0; j < n; ++j)
            {
                Mi[j] ^= (a & Bk[j]);
            }
        }
    }

    return M;
}
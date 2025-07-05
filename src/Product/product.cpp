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

std::vector<int> square_mat_product(const std::vector<int> &A, const std::vector<int> &B, const int n)
{

    std::vector<int> M(n * n);

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

std::vector<int> square_mat_product_omp(const std::vector<int> &A, const std::vector<int> &B, const int n)
{

    std::vector<int> M(n * n);

    int res = 0;
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
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

std::vector<int> square_mat_product_omp_init(const std::vector<int> &A, const std::vector<int> &B, const int n)
{

    std::vector<int> M(n * n, 0);

    int res = 0;
#ifdef USE_OPENMP
#pragma omp parallel for
#endif
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

std::vector<int> square_mat_product_omp_collapse(const std::vector<int> &A, const std::vector<int> &B, const int n)
{

    std::vector<int> M(n * n);

    int res = 0;
#ifdef USE_OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
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

std::vector<int> square_mat_product_omp_init_collapse(const std::vector<int> &A, const std::vector<int> &B, const int n)
{

    std::vector<int> M(n * n, 0);

    int res = 0;
#ifdef USE_OPENMP
#pragma omp parallel for collapse(2) schedule(static)
#endif
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

std::vector<int> square_mat_product_omp_simd(const std::vector<int> &A, const std::vector<int> &B, const int n)
{

    std::vector<int> M(n * n);

#pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i)
    {
        int *Mi = M.data() + i * n;
        const int *Ai = A.data() + i * n;

        for (int j = 0; j < n; ++j)
        {
            int sum = 0;
            const int *Bcol = B.data() + j; // B[k][j] is at Bcol[k*n]
#pragma omp simd reduction(+ : sum) aligned(Ai, Bcol : 64)
            for (int k = 0; k < n; ++k)
            {
                sum += Ai[k] * Bcol[k * n];
            }
            Mi[j] = sum;
        }
    }

    return M;
}

std::vector<int> square_mat_product_omp_reorder(const std::vector<int> &A, const std::vector<int> &B, const int n)
{
    std::vector<int> M(n * n);

#pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i)
    {
        int *Mi = M.data() + i * n;
        const int *Ai = A.data() + i * n;

        // zero row i
        for (int j = 0; j < n; ++j)
            Mi[j] = 0;

        // accumulate in k-outer, j-inner order
        for (int k = 0; k < n; ++k)
        {
            int a = Ai[k];
            const int *Bk = B.data() + k * n;
            for (int j = 0; j < n; ++j)
            {
                Mi[j] += a * Bk[j];
            }
        }
    }

    return M;
}

std::vector<int> square_mat_product_omp_reorder_init(const std::vector<int> &A, const std::vector<int> &B, const int n)
{
    std::vector<int> M(n * n, 0);

#pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i)
    {
        int *Mi = M.data() + i * n;
        const int *Ai = A.data() + i * n;

        // accumulate in k-outer, j-inner order
        for (int k = 0; k < n; ++k)
        {
            int a = Ai[k];
            const int *Bk = B.data() + k * n;
            for (int j = 0; j < n; ++j)
            {
                Mi[j] += a * Bk[j];
            }
        }
    }

    return M;
}

std::vector<int> square_mat_product_omp_reorder_simd(const std::vector<int> &A, const std::vector<int> &B, const int n)
{

    std::vector<int> M(n * n);

    // Parallelize over rows of A/M
#pragma omp parallel for schedule(static)
    for (int i = 0; i < n; ++i)
    {
        int *Mi = M.data() + i * n;       // pointer to row i of M
        const int *Ai = A.data() + i * n; // pointer to row i of A

        // Zero the entire row i of M
        for (int j = 0; j < n; ++j)
        {
            Mi[j] = 0;
        }

        // Accumulate outer product contributions for row i
        for (int k = 0; k < n; ++k)
        {
            int a = Ai[k];
            const int *Bk = B.data() + k * n; // pointer to row k of B

// Vectorize this inner loop over j
#pragma omp simd aligned(Mi, Bk : 64)
            for (int j = 0; j < n; ++j)
            {
                Mi[j] += a * Bk[j];
            }
        }
    }

    return M;
}

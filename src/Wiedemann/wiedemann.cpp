#include <vector>
#include <random>
#include <iostream>
#include "../Product/product.hpp"
#include "../Tools/tools.hpp"
#include "../Tools/vectors.hpp"

/*
 * Generate the Krulov subspace of A and v.
 */
std::vector<std::vector<char>> krylov_subspace(const std::vector<char> &A, const std::vector<char> &v, int d)
{
    // Initialize the vector of vectors with `n` vectors, each of size v.size()`
    std::vector<std::vector<char>> K(d, std::vector<char>(v.size()));
    K[0] = v;

    for (int i = 1; i < d; i++)
        K[i] = mat_vect_product_f2(A, K[i - 1]);
    return K;
}

/*
 * Generate random vectors u and v in F2^n such that u.v = 0.
 */
void set_u_v(std::vector<char> &u, std::vector<char> &v)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);
    for (int i = 0; i < v.size(); ++i)
    {
        v[i] = dis(gen);
        u[i] = dis(gen);
    }
    while (dot_product_f2(u, v) != 0)
    {
        for (int i = 0; i < v.size(); ++i)
        {
            u[i] = dis(gen);
        }
    }
}

std::vector<char> berlekamp_massey(std::vector<char> s)
{
    int n = s.size();
    std::vector<int> C(n + 1, 0);
    C[0] = 1;
    std::vector<int> B(n + 1, 0);
    B[0] = 1;
    std::vector<int> T;
    int L = 0;
    int m = 1;
    int d = 0;
    for (int i = 0; i < n; i++)
    {
        d = s[i];
        for (int j = 1; j < L + 1; j++)
            d ^= C[j] & s[i - j];
        if (d == 0)
            m++;
        else
        {
            T = C; // Deep copy
            for (int v = 0; v < i + 1; v++)
                if (v >= m)
                    C[v] ^= B[v - m];
            if (2 * L <= i)
            {
                L = i + 1 - L;
                B = T;
                m = 1;
            }
            else
                m++;
        }
    }
    // Return a part of the vector C from index 0 to L
    return std::vector<char>(C.begin(), C.begin() + L + 1);
}

/*
* Wiedemann algorithm to find a non-trivial solution of Ax = 0.
* A is a square matrix of size n x n.
* max_iteration is the maximum number of iterations to perform.
* Return an optional vector x such that Ax = 0, or std::nullopt if no solution is found.
*/
std::vector<char> wiedemann(std::vector<char> A, int n, int max_iteration)
{

    std::vector<char> u(n, 0);
    std::vector<char> v(n, 0);

    int iteration = 0;
    while (iteration < max_iteration)
    {
        iteration++;
        set_u_v(u, v);
        std::vector<std::vector<char>> Kv = krylov_subspace(A, v, 2 * n);

        std::vector<char> s(2 * n, 0);
        for (int i = 0; i < 2 * n; i++)
            s[i] = dot_product_f2(u, Kv[i]);

        std::vector<char> C = berlekamp_massey(s);
        int d = C.size() - 1;

        std::vector<int> q(d+1);
        for (int i = 0; i <= d; i++)
            q[i] = C[d - i];

        std::vector<char> w(n, 0);
        for (int i = 0; i <= d; i++)
        {
            if (q[i])
                for (int j = 0; j < n; j++)
                    w[j] = (w[j] + Kv[i][j]) % 2;
        }

        int sum_w = sum_vec(w);
        if (sum_w == 0)
            continue; // Get new (u,v) because w = 0
        else if (sum_w == 1)
            continue; // Get new (u,v) because w is one line
        else
        {
            std::vector<char> res = mat_vect_product_f2(A, w);
            if (sum_vec(res) == 0)
            {
                std::cout << "WIEDEMANN: found a solution in " << iteration << " iterations" << std::endl;
                return w;
            }
        }
    }
    throw std::runtime_error("WIEDEMANN: failed to find a solution after " + std::to_string(max_iteration) + " iterations");
    return std::vector<char>();
}
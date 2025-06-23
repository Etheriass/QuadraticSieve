#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <random>
#include <iostream>
#include "../Product/product.hpp"
#include "../Product/dotProduct.hpp"
#include "../Tools/tools.hpp"
#include <optional>

using namespace std;

vector<vector<int>> krylov_subspace(vector<int> &A, vector<int> v, int d)
{
    // Initialize the vector of vectors with `n` vectors, each of size v.size()`
    vector<vector<int>> K(d, vector<int>(v.size()));
    K[0] = v;

    for (int i = 1; i < d; i++)
        K[i] = mat_vect_product_F2(A, K[i - 1]);
    return K;
}

/*
 * Generate random vectors u and v in F2^n such that u.v = 0.
 */
void set_u_v(vector<int> &u, vector<int> &v)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    for (int i = 0; i < v.size(); ++i)
    {
        v[i] = dis(gen);
        u[i] = dis(gen);
    }
    while (dot_product(u, v) % 2 != 0)
    {
        for (int i = 0; i < v.size(); ++i)
        {
            u[i] = dis(gen);
        }
    }
}

vector<int> berlekamp_massey(vector<int> s)
{
    int n = s.size();
    vector<int> C(n + 1, 0);
    C[0] = 1;
    vector<int> B(n + 1, 0);
    B[0] = 1;
    vector<int> T;
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
    return std::vector<int>(C.begin(), C.begin() + L + 1);
}

optional<vector<int>> wiedemann(vector<int> A, int n, int max_iteration)
{

    vector<int> u(n, 0);
    vector<int> v(n, 0);

    int iteration = 0;
    while (iteration < max_iteration)
    {
        set_u_v(u, v);
        // printRowVec(u);
        // printRowVec(v);

        vector<vector<int>> Kv = krylov_subspace(A, v, 2 * n);
        // printColVec(Kv[0]);

        vector<int> s(2 * n, 0);
        for (int i = 0; i < 2 * n; i++)
            s[i] = dot_product(u, Kv[i]) % 2;
        // printRowVec(s);

        vector<int> C = berlekamp_massey(s);
        int d = C.size() - 1;
        if (C[d] != 0)
            continue; // Get new (u,v) because f(0) != 0

        vector<int> q(d);
        for (int i = 0; i < d; i++)
            q[i] = C[d - 1 - i];

        vector<int> w(n, 0);
        for (int i = 0; i < d; i++)
        {
            if (q[i])
                for (int j = 0; j < d; j++)
                    w[j] = (w[j] + Kv[i][j]) % 2;
        }

        int sum_w = sum_vec(w);
        if (sum_w == 0)
            continue; // Get new (u,v) because w = 0
        else if (sum_w == 1)
            continue; // Get new (u,v) because w is one line
        else
        {
            vector<int> r = mat_vect_product_F2(A, w);
            if (sum_vec(r) == 0)
            {
                return w;
            }
        }
        iteration++;
    }
    cout << "FAIL" << endl;
    return nullopt;
}
#include <vector>
#include <iostream>

int sum_vec(const std::vector<int> &u)
{
    int sum = 0;
    for (const int val : u)
        sum += val;
    return sum;
}

std::vector<int> vec_add(const std::vector<int> &u, const std::vector<int> &v)
{
    if (u.size() != v.size())
        throw std::invalid_argument("Vector addition: vectors should have the same size");
    std::vector<int> r(u.size());
    for (size_t i = 0; i < u.size(); i++)
        r[i] = u[i] + v[i];
    return r;
}

std::vector<int> vec_add_f2(const std::vector<int> &u, const std::vector<int> &v)
{
    if (u.size() != v.size())
        throw std::invalid_argument("Vector addition: vectors should have the same size");
    std::vector<int> r(u.size());
    for (size_t i = 0; i < u.size(); i++)
        r[i] = (u[i] + v[i]) % 2;
    return r;
}

void print_col_vec(const std::vector<int> &u)
{ // pass the vector by const reference to avoid unnecessary copying
    for (const int element : u)
        std::cout << element << std::endl;
}

void print_row_vec(const std::vector<int> &u)
{
    std::cout << "[";
    for (const int element : u)
        std::cout << element << " ";
    std::cout << "]" << std::endl;
}
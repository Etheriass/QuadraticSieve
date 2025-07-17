#include <vector>
#include <iostream>

int sum_vec(const std::vector<char> &u)
{
    int sum = 0;
    for (const char val : u)
        sum += val;
    return sum;
}

void print_col_vec(const std::vector<int> &u)
{
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
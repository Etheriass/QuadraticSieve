#ifndef PRODUCT_HPP
#define PRODUCT_HPP
#include <vector>

char dot_product_f2(const std::vector<char> &a,const std::vector<char> &b);

std::vector<char> mat_vect_product_f2(const std::vector<char> &A, const std::vector<char> &b);
std::vector<char> mat_vect_product_f2_enhanced(const std::vector<char> &A, const std::vector<char> &b);
std::vector<char> mat_product_f2(const std::vector<char> &A, const std::vector<char> &B, int n, int m);
std::vector<char> mat_product_f2_reorder(const std::vector<char> &A, const std::vector<char> &B, int n);

#endif
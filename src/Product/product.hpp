#ifndef PRODUCT_HPP
#define PRODUCT_HPP
#include <vector>

int dot_product(const std::vector<int> &a,const std::vector<int> &b);
int dot_product_f2(const std::vector<int> &a,const std::vector<int> &b);

std::vector<int> mat_vect_product(const std::vector<int> &A, const std::vector<int> &b);
std::vector<int> mat_vect_product_f2(const std::vector<int> &A, const std::vector<int> &b);
std::vector<int> mat_product_f2(const std::vector<int> &A, const std::vector<int> &B, int n, int m);
std::vector<int> square_mat_product_cpp(const std::vector<int> &A, const std::vector<int> &B, const int n);
std::vector<int> square_mat_product_cpp_parra_omp(const std::vector<int> &A, const std::vector<int> &B, const int n);
std::vector<int> square_mat_product_cpp_parra_omp_init(const std::vector<int> &A, const std::vector<int> &B, const int n);
std::vector<int> square_mat_product_cpp_parra_omp_collapse(const std::vector<int> &A, const std::vector<int> &B, const int n);
std::vector<int> square_mat_product_cpp_parra_omp_pthread(const std::vector<int> &A, const std::vector<int> &B, const int n);

#endif
#ifndef PRODUCT_PTHREAD_HPP
#define PRODUCT_PTHREAD_HPP

#include <vector>

std::vector<int> square_mat_product_pthread(const std::vector<int> &A, const std::vector<int> &B, int n, int num_threads);
std::vector<int> square_mat_product_pthread_affinity(const std::vector<int> &A, const std::vector<int> &B, int n, int num_threads);

#endif
#ifndef PRODUCT_HPP
#define PRODUCT_HPP
#include <vector>

int** mat_product(int** A, int* shape_A, int** B, int* shape_B);

int** square_mat_product(int** A, int** B, int n);
int* square_mat_product_flat(int* A, int* B, int n);
int* square_mat_product_flat_parra(int* A, int* B, int n);
std::vector<int> square_mat_product_cpp(std::vector<int> A, std::vector<int> B, int n);
std::vector<int> square_mat_product_cpp_parra(std::vector<int> A, std::vector<int> B, int n);

int** square_mat_product_parra(int** A, int** B, int n);

int** mat_4x4_product(int**A, int** B);

int** mat_2x2_product(int**A, int** B);

int** mat_4x4_product_alphatensor_Z2Z(int**A, int** B);

#endif
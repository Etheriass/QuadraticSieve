#ifndef PRODUCT_H
#define PRODUCT_H

int** mat_product(int** A, int* shape_A, int** B, int* shape_B);

int** square_mat_product(int** A, int** B, int n);

int** square_mat_product_parra(int** A, int** B, int n);

int** mat_4x4_product(int**A, int** B);

int** mat_2x2_product(int**A, int** B);

int** mat_4x4_product_alphatensor_Z2Z(int**A, int** B);

#endif
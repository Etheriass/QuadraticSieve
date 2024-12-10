#ifndef DAC_MULTIPLICATION_PARRA_H
#define DAC_MULTIPLICATION_PARRA_H

/*
* Divide and Conquer Matrix Multiplication
* ----------------------------------------
* This function takes two square matrices A and B of size n x n and returns 
* the product of the two matrices using the divide and conquer approach.
* - A: a square matrix of size n x n
* - B: a square matrix of size n x n
* - n: the size of the matrices A and B
*
* returns: 
* - the product of the two matrices A and B
*
*/
int** dac_square_mat_product_parra(int** A, int** B, int n, int deallocate);

#endif
#ifndef DAC_TOOLS_H
#define DAC_TOOLS_H

/*
* Add Matrices
* ------------
* Adds two square matrices A and B of size n x n and stores the result in matrix C.
* - A: a square matrix of size n x n
* - B: a square matrix of size n x n
* - C: a square matrix of size n x n
* - n: the size of the matrices A, B, and C
*/
void add_square_matrices(int **A, int **B, int**C, int n, int deallocate);

/*
* Subtract Matrices
* -----------------
* Subtracts two square matrices A and B of size n x n and stores the result in matrix C.
* - A: a square matrix of size n x n
* - B: a square matrix of size n x n
* - C: a square matrix of size n x n
* - n: the size of the matrices A, B, and C
*/
void subtract_square_matrices(int **A, int **B, int**C, int n);


int **add(int **A, int **B, int n, int deallocate);

int **sub(int **A, int **B, int n, int deallocate);


#endif
#ifndef TOOLS_HPP
#define TOOLS_HPP

/*
* Transpose a matrix
* ------------------
* A: matrix to transpose
* T: transposed matrix
* n: number of rows of A
* m: number of columns of A
*/
// void transpose(int *A, int *T, int n, int m);
std::vector<int> transpose(std::vector<int> A, int n, int m);

void printMatrix(const std::vector<int> &A, int n, int m);

/*
* Print a matrix
* --------------
* A: matrix to print
* n: number of rows of A
* m: number of columns of A
*/
void printArrayMatrix(int **A, int n, int m);

/*
* Print square a matrix
* --------------
* A: matrix to print
* n: number of rows and columns of A
*/
void print_square_matrix(int **A, int n);

/*
* Allocate Matrix
* ---------------
* Allocates memory for a 2D matrix of size rows x cols.
* - M: a pointer to a pointer to an integer matrix
* - rows: the number of rows in the matrix
* - cols: the number of columns in the matrix
* returns:
* - the allocated square matrix
*/
int** allocate_matrix( int rows, int cols);

/*
* Allocate square Matrix
* ---------------
* Allocates memory for a 2D square matrix of size n.
* - M: a pointer to a pointer to an integer matrix
* - n: the number of rows and columns in the matrix
* returns:
* - the allocated square matrix
*/
int** allocate_square_matrix(int n, int value = 0);
// In C++, default parameters should be specified only once—and that should be in the function declaration, not the definition.


/*
* Free Matrix
* -----------
* Frees the memory allocated for a 2D matrix.
* - M: a pointer to an integer matrix
* - rows: the number of rows in the matrix
*/
void free_matrix(int **M, int rows);

/*
 * Is Matrix Equal
 * ---------------
 * Check if two matrices are equal.
 * - A: a square matrix of size n x n
 * - B: a square matrix of size n x n
 * returns:
 * - 1 if the matrices are equal, 0 otherwise
 */
int is_matrix_equal(int **A, int **B, int n);

/*
 * Is Matrix Equal in Z2
 * ---------------------
 * Check if two matrices are equal in Z/2Z.
 * - A: a square matrix of size n x n
 * - B: a square matrix of size n x n
 * returns:
 * - 1 if the matrices are equal, 0 otherwise
 */
int is_matrix_equal_in_Z2(int **A, int **B, int n);

#endif
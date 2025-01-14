#include <string.h>
#include <stdio.h>
#include "../src/Tools/tools.h"

int main()
{
    int N = 3;
    int M = 4;
    int **A = allocate_matrix(N, M);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            A[i][j] = i + j;
        }
    }

    int** B = allocate_square_matrix(N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            B[i][j] = (i*j*10);
        }
    }

    printMatrix(A, N, M);

    print_square_matrix(B, N);
    return 0;
}
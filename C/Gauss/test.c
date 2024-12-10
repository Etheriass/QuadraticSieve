
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Tools/Tools.h"
#include "Gauss.h"

int main()
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int rows, cols;

    rows = 1000;
    cols = 1000;

    // printf("Enter the number of rows and columns (space-separated): ");
    // scanf("%d %d", &rows, &cols);

    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int *)malloc((cols + 1) * sizeof(int));

    for (int i = 0; i < rows; i++)
    {
        matrix[i][cols] = i;
        for (int j = 0; j < cols; j++)
            matrix[i][j] = rand() % 2;
    }

    // [1,1,1]
    // [1,0,1]
    // [0,0,1]
    // [1,1,0]
    // matrix[0][0] = 1;
    // matrix[0][1] = 1;
    // matrix[0][2] = 1;
    // matrix[1][0] = 1;
    // matrix[1][1] = 0;
    // matrix[1][2] = 1;
    // matrix[2][0] = 0;
    // matrix[2][1] = 0;
    // matrix[2][2] = 1;
    // matrix[3][0] = 1;
    // matrix[3][1] = 1;
    // matrix[3][2] = 0;

    printf("Original matrix:\n");
    printMatrix(matrix, rows, cols + 1);

    gaussianElimination(matrix, rows, cols);

    printf("\nEchelon matrix:\n");
    printMatrix(matrix, rows, cols + 1);

    // reducedForm(matrix, rows, cols);
    // printf("\nReduced echelon matrix:\n");
    // printMatrix(matrix, rows, cols + 1);

    // Free allocated memory
    for (int i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
    return 0;
}
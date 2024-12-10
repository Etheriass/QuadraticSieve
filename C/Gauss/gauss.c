#include <stdio.h>
#include <stdlib.h>

/*
 * Gaussian-Jordan elimination
 * ---------------------------
 * mat: matrix to echelonize
 * rows: number of rows of mat
 * cols: number of columns of mat
 */
void gaussianElimination(int **mat, int rows, int cols)
{
    for (int i = 0; i < rows - 1; i++)
    { // for every row
        if (mat[i][i])
        { // if row is a pivot
            for (int j = i + 1; j < rows; j++)
            { // for every following row
                if (mat[j][i])
                { // if the row has 1 under the diagonal
                    for (int l = i; l < cols; l++)
                    {
                        mat[j][l] = (mat[j][l] + mat[i][l]) % 2; // we add the pivot row
                    }
                    // mat[j][cols] = mat[j][cols] + mat[i][cols];
                }
            }
        }
        else
        { // if row not a pivot : change with the first pivot
            int r = i + 1;
            while (mat[r][i] == 0)
            {
                r++;
                if (r == rows)
                    break;
            }
            if (r < rows)
            {
                int *newPivot = (int *)malloc((cols) * sizeof(int));
                for (int v = 0; v < cols; v++)
                {
                    newPivot[v] = mat[r][v];
                    mat[r][v] = mat[i][v];
                    mat[i][v] = newPivot[v];
                }
                int ref = mat[r][cols];
                // printf("ref : %d\n", ref);
                mat[r][cols] = mat[i][cols];
                mat[i][cols] = ref;
                for (int j = i + 1; j < rows; j++)
                { // for every following row
                    if (mat[j][i])
                    { // if the row has 1 under the diagonal
                        for (int l = i; l < cols; l++)
                        {
                            mat[j][l] = (mat[j][l] + mat[i][l]) % 2; // we add the pivot row
                        }
                        // mat[j][cols] = mat[j][cols] + mat[i][cols];
                    }
                }
            }
        }
    }
}

/*
 * Reduced row echelon form
 * ------------------------
 * mat: matrix to reduce
 * rows: number of rows of mat
 * cols: number of columns of mat
 */
void reducedForm(int **mat, int rows, int cols)
{
    int i, j, k;
    for (i = rows - 1; i >= 0; i--) // for every row starting from the bottom
    {
        if (mat[i][i]) // if row is a pivot
        {
            for (j = i - 1; j >= 0; j--) // for every row above
            {
                if (mat[j][i]) // if the row is a pivot
                {
                    for (k = i; k < cols; k++) // for every column
                    {
                        mat[j][k] = (mat[j][k] + mat[i][k]) % 2;
                    }
                }
            }
        }
    }
}
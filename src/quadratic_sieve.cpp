#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "Eratosthene/eratosthene.hpp"
#include "Friables/friables.h"
#include "Tools/tools.h"
#include "Factorization/factorization.h"
#include "Krylov/krylov.h"

int main() {
    unsigned long long N = 184467440737095601;//17595551;18446744073709551615
    printf("Factorisation of %llu: \n", N);

    clock_t start, end;
    start = clock();

    // Collection phase
    int B = (int)exp(0.5*sqrt(log(N) * log(log(N))))+120;
    printf("Choosen B: %d\n", B);

    int piB;
    int* primes = eratostheneSieve(B, &piB);
    if (primes == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    int A = 102000;

    printf("Number of square to find: %d\n", piB);
    printf("Sieving interval: [%d, %d]\n", (int)sqrt(N) + 1, (int)sqrt(N) + A);
    
    // int nbQf;
    // unsigned long long *Qf = QBfriablesV2Long(B, N, A, &nbQf);
    // printf("Number of Q-B-Friable numbers in [%d, %d]: %d\n", (int)sqrt(N) + 1, (int)sqrt(N) + A, nbQf);

    // int **M = (int**)malloc(nbQf * sizeof(int*));
    // for (int i = 0; i < nbQf; i++)
    // {
    //     M[i] = (int*)malloc((piB) * sizeof(int));
    // }

    // for (int i = 0; i < nbQf; i++)
    // {
    //     int *factors = factorizationMod2(Qf[i], primes, piB);
    //     for (int j = 0; j < piB; j++)
    //     {
    //         M[i][j] = factors[j];
    //     }
    //     if (i == nbQf - 1){
    //         free(factors);
    //     }
    // }
    // // printMatrix(M, nbQf, piB);

    // end = clock();
    // double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time taken for the collection phase: %f seconds\n", cpu_time_used);

    // // Processing phase
    // start = clock();

    // int* b = malloc(piB * sizeof(int));
    // for (int i = 0; i < piB; i++){
    //     b[i] = 1;
    // }

    // int*** K = krylov_subspace(M, b, piB);

    // end = clock();
    // cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    // printf("Time taken for the proccessing phase: %f seconds\n", cpu_time_used);

    // // Free
    // for(int i = 0; i < nbQf; i++) {
    //     free(M[i]);
    // }
    // free(M);
    // free(Qf);
    // free(primes);

    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include "../src/Eratosthene/eratosthene.h"

int main() {
    
    double start, end, cpu_time_used;
    start = omp_get_wtime();

    int n = 100; // Set your desired value of n
    int resultSize;
    int* primes = eratostheneSieve(n, &resultSize);

    printf("Prime numbers less than %d: ", n);
    for (int i = 0; i < resultSize; ++i) {
        printf("%d ", primes[i]);
    }
    printf("\n Number of prime numbers: %d\n", resultSize);

    end = omp_get_wtime();

    free(primes);
    cpu_time_used = end - start;
    printf("Time taken: %f seconds\n", cpu_time_used);
    return 0;
}

// 100000 : 1,8s
// 1000000 : 192s
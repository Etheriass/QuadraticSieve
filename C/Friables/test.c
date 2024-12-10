#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "friables.h"

int testBfriables(int X, int B)
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int *f = Bfriables(B, X);

    printf("B-Friable numbers in [2, %d]: ", X);
    int count = 0;
    for (int i = 2; i <= X; ++i)
    {
        if (f[i] == 1)
        {
            // printf("%d ", i);
            count++;
        }
    }
    printf("\n");
    printf("Number of B-Friable numbers in [2, %d]: %d\n", X, count);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
    return 0;
}

int testBfriablesV2(int X, int B)
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int *f = BfriablesV2(B, X);

    printf("B-Friable numbers in [2, %d]: ", X);
    int count = 0;
    for (int i = 2; i <= X; ++i)
    {
        if (f[i] == 1)
        {
            // printf("%d ", i);
            count++;
        }
    }
    printf("\n");
    printf("Number of B-Friable numbers in [2, %d]: %d\n", X, count);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
    return 0;
}

int testQBfriables(int B, int N, int A)
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int nbQf;
    int *Qf = QBfriables(B, N, A, &nbQf);
    if (nbQf == 0)
    {
        printf("No Qf found\n");
        return 0;
    }
    printf("%d QB-Friable entre %d et %d: ", nbQf, (int)sqrt(N) + 1, (int)sqrt(N) + A);
    for (int i = 0; i < nbQf; i++)
    {
        printf("%d ", Qf[i]);
    }
    printf("\n");

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
    return 0;
}

int testQBfriablesV2(int B, int N, int A)
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int nbQf;
    int *Qf = QBfriablesV2(B, N, A, &nbQf);
    if (nbQf == 0)
    {
        printf("No Qf found\n");
        return 0;
    }
    printf("%d QB-Friable entre %d et %d: ", nbQf, (int)sqrt(N) + 1, (int)sqrt(N) + A);
    for (int i = 0; i < nbQf; i++)
    {
        printf("%d ", Qf[i]);
    }
    printf("\n");

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
    return 0;
}

int testQBfriablesV2Long(int B, unsigned long long int N, int A)
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    int nbQf;
    unsigned long long int *Qf = QBfriablesV2Long(B, N, A, &nbQf);
    if (nbQf == 0)
    {
        printf("No Qf found\n");
        return 0;
    }
    // printf("%d QB-Friable entre %d et %d: ", nbQf, (unsigned long long)sqrt(N) + 1, (int)sqrt(N) + A);
    for (int i = 0; i < nbQf; i++)
    {
        printf("%lld ", Qf[i]);
    }
    printf("\n");

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("%d QB-Friable entre %llu et %llu: ", nbQf, (unsigned long long)sqrt(N) + 1, (unsigned long long)sqrt(N) + A);
    printf("Time taken: %f seconds\n", cpu_time_used);
    return 0;
}


int main()
{
    // testBfriables(10000000, 3);
    // testBfriablesV2(10000000, 3);
    // testQBfriables(250, 43338011, 10000000);
    // testQBfriablesV2(250, 43338011, 100000000);
    // testQBfriables(25, 4333801, 1000);
    // testQBfriablesV2(100, 4333801, 1000);
    testQBfriablesV2Long(500, 14757395258967641297ULL, 190000000);
    // testQBfriablesV2Long(20, 18446744073709551615ULL, 100);
    // testQBfriablesV3Long(500, 14757395258967641297ULL, 100000000);

    return 0;
}
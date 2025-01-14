#include <stdio.h>
#include "../src/Legendre/legendre.h"

int main()
{
    int m = 35;
    int N = 3;
    // printf("m = ");
    // scanf("%d", &m);
    // printf("N = ");
    // scanf("%d", &N);
    int res = Legendre(m, N);
    printf("Legendre(%d, %d) = ", m, N);
    printf("%d\n", res);
    return 0;
}
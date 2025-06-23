#ifndef FRIABLES_H
#define FRIABLES_H

/*
* Sieve of integers B-smooth
* -------------------------------------
* max : the maximum number to check
* B : the smoothness bound

* returns: an array where '1' represent the B-smooth numbers
*/
int* Bfriables( int B, int max);
int* BfriablesV2( int B, int max);
int* QBfriables(int B, int N, int A, int* size);
int* QBfriablesV2(int B, int N, int A, int* size);

unsigned long long *QBfriablesV2Long(int B, unsigned long long N,int A, int *size, unsigned long long *X);
#endif
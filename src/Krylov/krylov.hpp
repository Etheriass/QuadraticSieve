#ifndef KRYLOV_HPP
#define KRYLOV_HPP

int** krylov_subspace_flat(int* A, int*b, int n);
int*** krylov_subspace(int** A, int*b, int n);

#endif
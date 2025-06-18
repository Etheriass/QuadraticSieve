#ifndef KRYLOV_HPP
#define KRYLOV_HPP


int** krylov_subspace_flat(int* A, int*b, int n);
std::vector<std::vector<int>> krylov_subspace(std::vector<int> A, std::vector<int>b, int n);

#endif
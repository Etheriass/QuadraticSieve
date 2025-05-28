#include <iostream>
#include <chrono>
#include <math.h>
#include "../src/Eratosthene/eratosthene.hpp"
#include "../src/Friables/friables.hpp"
#include "../src/Krylov/krylov.hpp"
#include "../src/Tools/tools.hpp"


void benchmark(){
    auto start = std::chrono::high_resolution_clock::now();

    unsigned long long N = 184467440737095601;

    // std::vector<int> primes = eratostheneSieve(N);
    // int B = (int)exp(0.5*sqrt(log(N) * log(log(N))));
    // int A = 1002000;
    // int nbQf;
    // unsigned long long *Qf = QBfriablesV2Long(B, N, A, &nbQf);
    // std::cout << nbQf << std::endl;


    int piB = 350;
    int* b = (int*)malloc(piB * sizeof(int));
    for (int i = 0; i < piB; i++){
        b[i] = 1;
    }
    // int** A = allocate_square_matrix(piB);
    int* A = (int*)calloc(piB*piB, sizeof(int));

    int** K = krylov_subspace_flat(A,b,piB);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "============================\n";
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    std::cout << "============================\n";
}

int main(){
    // benchmark();
    return 0;
}

#include <iostream>
#include <chrono>
#include "../src/Eratosthene/eratosthene.hpp"


void benchmark(){
    auto start = std::chrono::high_resolution_clock::now();

    int N = 1000000;

    std::vector<int> primes = eratostheneSieve(N);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "============================\n";
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    std::cout << "============================\n";
}

int main(){
    benchmark();
    return 0;
}

#include <iostream>
#include <chrono>
#include "Tools/tools.hpp"
#include <vector>

using Clock = std::chrono::steady_clock;


void naive(std::vector<std::string> args = {}) {
    bool found = false;

    __uint128_t N = parse_u128(args[0]);
    __uint128_t sqrt_N = sqrt_128(N);

    std::cout << "Factorization of: " << to_str(N);

    auto start = Clock::now();

    for (__uint128_t i = 3; i <= sqrt_N; i+= 2){
        if (N % i == 0) {
            std::cout << " : "<< to_str(i);
            found = true;
            break;
        }
    }
    if (!found) {
        std::cout << " : ERROR";
    }
    auto end = Clock::now();
    std::chrono::duration<double> dur = end - start;
    std::cout << " in: " << dur.count() << "s\n" << std::endl;
}


int main(int argc, char* argv[]) {
    if (argc > 1) {
        naive({argv[1]});
    } else {
        std::cerr << "Please provide a number to factor." << std::endl;
    }
    return 0;
}
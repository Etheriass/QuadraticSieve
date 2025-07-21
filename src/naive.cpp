#include <iostream>
#include <chrono>
#include <iomanip>
#include "Tools/tools.hpp"

using Clock = std::chrono::steady_clock;

void print_progress(double progress, double elapsed, double estimated_total) {
    int barWidth = 50;
    std::cout << "\r[";
    int pos = static_cast<int>(barWidth * progress);
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << std::fixed << std::setprecision(2) << (progress * 100.0) << "%";
    std::cout << " | Elapsed: " << std::setprecision(1) << elapsed << "s";
    if (progress) {
        std::cout << " | ETA: " << std::setprecision(1) << (estimated_total - elapsed) << "s";
    }
    std::cout.flush();
}

void naive(){
    __uint128_t N = parse_u128("18446744073709551617"); 
    __uint128_t sqrt_N = sqrt_128(N);
    auto start = Clock::now();
    bool found = false;
    const __uint128_t progress_step = sqrt_N / 1000 ? sqrt_N / 1000 : 1; // update every ~0.1%

    for (__uint128_t i = 2; i < sqrt_N; i++){
        double progress = static_cast<double>(i) / static_cast<double>(sqrt_N);
        auto now = Clock::now();
        std::chrono::duration<double> elapsed = now - start;
        double estimated_total = progress ? elapsed.count() / progress : 0.0;
        print_progress(progress, elapsed.count(), estimated_total);
        if (N % i == 0) {
            std::cout << "\nFactor found:" << to_str(i) << std::endl;
            found = true;
            break;
        }
    }
    if (!found) {
        auto now = Clock::now();
        std::chrono::duration<double> elapsed = now - start;
        print_progress(1.0, elapsed.count(), elapsed.count());
    }
    std::cout << std::endl;
    auto end = Clock::now();
    std::chrono::duration<double> dur = end - start;
    std::cout << "Took:" << dur.count() << "s" << std::endl;
}
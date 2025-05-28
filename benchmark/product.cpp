#include <benchmark/benchmark.h>
#include <vector>
#include <random>
#include "../src/Product/product.hpp"
#include "../src/Tools/tools.hpp"

// Helper to generate a random square matrix as a flat vector
std::vector<int> random_square_matrix(int n) {
    std::vector<int> mat(n * n);
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 100);
    for (int& x : mat) x = dist(rng);
    return mat;
}

static void BM_SquareMatProductCpp(benchmark::State& state) {
    int n = state.range(0);
    std::vector<int> A = random_square_matrix(n);
    std::vector<int> B = random_square_matrix(n);

    for (auto _ : state) {
        auto result = square_mat_product_cpp(A, B, n);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_SquareMatProductCpp)->Arg(256)->Arg(1024);

static void BM_SquareMatProductCppParra(benchmark::State& state) {
    int n = state.range(0);
    std::vector<int> A = random_square_matrix(n);
    std::vector<int> B = random_square_matrix(n);

    for (auto _ : state) {
        auto result = square_mat_product_cpp_parra(A, B, n);
        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(BM_SquareMatProductCppParra)->Arg(256)->Arg(1024);

BENCHMARK_MAIN();

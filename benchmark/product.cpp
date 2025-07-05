#include <benchmark/benchmark.h>
#include <vector>
#include <random>
#include "../src/Product/product.hpp"
#include "../src/Tools/tools.hpp"

#ifdef USE_PTHREAD
#include "../src/Product/product_pthread.hpp"
#include <pthread.h>
#include <thread>
#endif

#define ARGS        \
    ->Arg(512)      \
        ->Arg(1024) \
        ->Arg(2048) \
        ->Iterations(3) // ->Arg(2400)  \
    // ->UseRealTime()

// Helper to generate a random square matrix as a flat vector
std::vector<int> random_square_matrix(int n)
{
    std::vector<int> mat(n * n);
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(0, 100);
    for (int &x : mat)
        x = dist(rng);
    return mat;
}

// Template function to benchmark any matrix multiplication function
template <typename Func>
static void BM_matrix_product_template(benchmark::State &state, Func func)
{
    int n = state.range(0);
    std::vector<int> A = random_square_matrix(n);
    std::vector<int> B = random_square_matrix(n);

    for (auto _ : state)
    {
        auto result = func(A, B, n);
        benchmark::DoNotOptimize(result);
    }
}

// Register benchmarks with lambda wrappers
BENCHMARK_CAPTURE(BM_matrix_product_template, square_mat_product_cpp,
                  [](const std::vector<int> &A, const std::vector<int> &B, int n)
                  {
                      return square_mat_product(A, B, n);
                  })
    ->Arg(1024);

#ifdef USE_OPENMP
BENCHMARK_CAPTURE(BM_matrix_product_template, square_mat_product_omp,
                  [](const std::vector<int> &A, const std::vector<int> &B, int n)
                  {
                      return square_mat_product_omp(A, B, n);
                  })
ARGS;

BENCHMARK_CAPTURE(BM_matrix_product_template, square_mat_product_omp_init,
                  [](const std::vector<int> &A, const std::vector<int> &B, int n)
                  {
                      return square_mat_product_omp_init(A, B, n);
                  })
ARGS;

BENCHMARK_CAPTURE(BM_matrix_product_template, square_mat_product_omp_collapse,
                  [](const std::vector<int> &A, const std::vector<int> &B, int n)
                  {
                      return square_mat_product_omp_collapse(A, B, n);
                  })
ARGS;

BENCHMARK_CAPTURE(BM_matrix_product_template, square_mat_product_omp_init_collapse,
                  [](const std::vector<int> &A, const std::vector<int> &B, int n)
                  {
                      return square_mat_product_omp_init_collapse(A, B, n);
                  })
ARGS;

BENCHMARK_CAPTURE(BM_matrix_product_template, square_mat_product_omp_simd,
                  [](const std::vector<int> &A, const std::vector<int> &B, int n)
                  {
                      return square_mat_product_omp_simd(A, B, n);
                  })
ARGS;

BENCHMARK_CAPTURE(BM_matrix_product_template, square_mat_product_omp_reorder,
                  [](const std::vector<int> &A, const std::vector<int> &B, int n)
                  {
                      return square_mat_product_omp_reorder(A, B, n);
                  })
ARGS;

BENCHMARK_CAPTURE(BM_matrix_product_template, square_mat_product_omp_reorder_init,
                  [](const std::vector<int> &A, const std::vector<int> &B, int n)
                  {
                      return square_mat_product_omp_reorder_init(A, B, n);
                  })
ARGS;

BENCHMARK_CAPTURE(BM_matrix_product_template, square_mat_product_omp_reorder_simd,
                  [](const std::vector<int> &A, const std::vector<int> &B, int n)
                  {
                      return square_mat_product_omp_reorder_simd(A, B, n);
                  })
ARGS;

#endif

#ifdef USE_PTHREAD
BENCHMARK_CAPTURE(BM_matrix_product_template, square_mat_product_pthread,
                  [](const std::vector<int> &A, const std::vector<int> &B, int n)
                  {
                      return square_mat_product_pthread(A, B, n, std::thread::hardware_concurrency());
                  })
ARGS;

BENCHMARK_CAPTURE(BM_matrix_product_template, square_mat_product_pthread_affinity,
                  [](const std::vector<int> &A, const std::vector<int> &B, int n)
                  {
                      return square_mat_product_pthread_affinity(A, B, n);
                  })
ARGS;

BENCHMARK_CAPTURE(BM_matrix_product_template, square_mat_product_pthread_affinity_hyperthread,
                  [](const std::vector<int> &A, const std::vector<int> &B, int n)
                  {
                      return square_mat_product_pthread_affinity_hyperthread(A, B, n, std::thread::hardware_concurrency());
                  })
ARGS;
#endif

BENCHMARK_MAIN();

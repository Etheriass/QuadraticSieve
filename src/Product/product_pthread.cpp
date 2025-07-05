#include <iostream>
#include <vector>
#include <pthread.h>
#include <cstdlib>      // posix_memalign
#include <unistd.h>     // sysconf
#include "product_pthread.hpp"


// Struct to hold each thread's arguments
struct ThreadArgs
{
    const int *A;
    const int *B;
    int *M;
    int n;
    int row_start;
    int row_end;
};

// Worker: computes M[i][j] for row_start ≤ i < row_end
void *matmul_worker(void *arg)
{
    ThreadArgs *args = static_cast<ThreadArgs *>(arg);
    const int *A = args->A;
    const int *B = args->B;
    int *M = args->M;
    int n = args->n;

    for (int i = args->row_start; i < args->row_end; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int sum = 0;
            for (int k = 0; k < n; ++k)
            {
                sum += A[i * n + k] * B[k * n + j];
            }
            M[i * n + j] = sum;
        }
    }
    return nullptr;
}

std::vector<int> square_mat_product_pthread(const std::vector<int> &A, const std::vector<int> &B, int n, int num_threads)
{
    std::vector<int> M(n * n);
    std::vector<pthread_t> threads(num_threads);
    std::vector<ThreadArgs> args(num_threads);

    int rows_per_thread = n / num_threads;
    for (int t = 0; t < num_threads; ++t)
    {
        int start = t * rows_per_thread;
        int end = (t == num_threads - 1) ? n : start + rows_per_thread;

        args[t] = ThreadArgs{A.data(), B.data(), M.data(), n, start, end};

        int rc = pthread_create(&threads[t], nullptr, matmul_worker, &args[t]);
        if (rc)
        {
            std::cerr << "Error: pthread_create returned " << rc << "\n";
            std::exit(1);
        }
    }

    // join
    for (auto &th : threads)
    {
        pthread_join(th, nullptr);
    }

    return M;
}

// Aligned version to avoid false sharing
// This version uses posix_memalign to ensure 64-byte alignment of buffers

struct ThreadArgsAligned {
    const int* A __attribute__((aligned(64)));
    const int* B __attribute__((aligned(64)));
    int*       M __attribute__((aligned(64)));
    int        n;
    int        row_start, row_end;
};

void* matmul_worker_aligned(void* v) {
    auto* args = static_cast<ThreadArgsAligned*>(v);
    const int* A = args->A;
    const int* B = args->B;
    int*       M = args->M;
    int        n = args->n;

    constexpr int TILE = 64;  // adjust to cache size

    for (int i = args->row_start; i < args->row_end; i += TILE) {
        int i_max = std::min(i + TILE, args->row_end);
        for (int j = 0; j < n; j += TILE) {
            int j_max = std::min(j + TILE, n);
            for (int ii = i; ii < i_max; ++ii) {
                for (int jj = j; jj < j_max; ++jj) {
                    int sum = 0;
                    // software prefetch next block of A and B
                    __builtin_prefetch(&A[ii*n + 0], 0, 1);
                    __builtin_prefetch(&B[0*n + jj], 0, 1);
                    for (int k = 0; k < n; ++k) {
                        sum += A[ii*n + k] * B[k*n + jj];
                    }
                    M[ii*n + jj] = sum;
                }
            }
        }
    }
    return nullptr;
}

std::vector<int> square_mat_product_pthread_affinity(
    const std::vector<int>& A,
    const std::vector<int>& B,
    int n,
    int num_threads)
{
    // --- 2) aligned buffers to avoid false sharing ---
    // (std::vector itself won't guarantee 64-byte alignment)
    int *a, *b, *m;
    if (posix_memalign((void**)&a, 64, sizeof(int)*n*n) != 0 ||
        posix_memalign((void**)&b, 64, sizeof(int)*n*n) != 0 ||
        posix_memalign((void**)&m, 64, sizeof(int)*n*n) != 0) {
        std::cerr << "posix_memalign failed\n";
        std::exit(1);
    }
    std::copy(A.begin(), A.end(), a);
    std::copy(B.begin(), B.end(), b);

    // --- 3) THREAD SETUP ---
    std::vector<pthread_t>    threads(num_threads);
    std::vector<ThreadArgsAligned>   args(num_threads);
    std::vector<pthread_attr_t> attrs(num_threads);

    int rows_per = n / num_threads;
    for (int t = 0; t < num_threads; ++t) {
        // compute start/end
        int start = t * rows_per;
        int end   = (t+1==num_threads ? n : start + rows_per);

        // init thread‐attributes
        pthread_attr_init(&attrs[t]);

        // set affinity: pin thread t to core (t mod #cores)
        cpu_set_t cpus;
        CPU_ZERO(&cpus);
        int ncores = sysconf(_SC_NPROCESSORS_ONLN);
        CPU_SET(t % ncores, &cpus);
        pthread_attr_setaffinity_np(
            &attrs[t],
            sizeof(cpu_set_t),
            &cpus
        );

        // fill args
        args[t] = ThreadArgsAligned{ a, b, m, n, start, end };

        // spawn
        int rc = pthread_create(
            &threads[t],
            &attrs[t],
            matmul_worker_aligned,
            &args[t]
        );
        if (rc) {
            std::cerr << "pthread_create failed: " << rc << "\n";
            std::exit(1);
        }
    }

    // join
    for (int t = 0; t < num_threads; ++t) {
        pthread_join(threads[t], nullptr);
        pthread_attr_destroy(&attrs[t]);
    }

    // copy out & free
    std::vector<int> M(m, m + n*n);
    free(a); free(b); free(m);
    return M;
}

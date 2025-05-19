#define BOOST_TEST_MODULE EratostheneTest
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <cstdlib>

#include "../src/Eratosthene/eratosthene.hpp"


BOOST_AUTO_TEST_CASE(test_small_primes) {
    std::vector<int> primes = eratostheneSieve(10);
    int resultSize = primes.size();

    std::vector<int> expected = {2, 3, 5, 7};
    BOOST_CHECK_EQUAL_COLLECTIONS(primes.begin(), primes.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(test_large_primes) {
    std::vector<int> primes = eratostheneSieve(50);
    int resultSize = primes.size();

    std::vector<int> expected = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    BOOST_CHECK_EQUAL_COLLECTIONS(primes.begin(), primes.end(), expected.begin(), expected.end());
}


// #include <stdlib.h>
// #include <stdio.h>
// #include <omp.h>
// #include "../src/Eratosthene/eratosthene.h"

// int main() {
    
//     double start, end, cpu_time_used;
//     start = omp_get_wtime();

//     int n = 100; // Set your desired value of n
//     int resultSize;
//     int* primes = eratostheneSieve(n, &resultSize);

//     printf("Prime numbers less than %d: ", n);
//     for (int i = 0; i < resultSize; ++i) {
//         printf("%d ", primes[i]);
//     }
//     printf("\n Number of prime numbers: %d\n", resultSize);

//     end = omp_get_wtime();

//     free(primes);
//     cpu_time_used = end - start;
//     printf("Time taken: %f seconds\n", cpu_time_used);
//     return 0;
// }

// 100000 : 1,8s
// 1000000 : 192s
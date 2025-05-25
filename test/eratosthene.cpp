#define BOOST_TEST_MODULE EratostheneTest
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <cstdlib>

#include "../src/Eratosthene/eratosthene.hpp"


BOOST_AUTO_TEST_CASE(test_empty_primes) {
    std::vector<int> primes = eratostheneSieve(1);
    std::vector<int> expected = {};
    BOOST_CHECK_EQUAL_COLLECTIONS(primes.begin(), primes.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(test_small_primes) {
    std::vector<int> primes = eratostheneSieve(10);
    std::vector<int> expected = {2, 3, 5, 7};
    BOOST_CHECK_EQUAL_COLLECTIONS(primes.begin(), primes.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(test_large_primes) {
    std::vector<int> primes = eratostheneSieve(50);
    std::vector<int> expected = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    BOOST_CHECK_EQUAL_COLLECTIONS(primes.begin(), primes.end(), expected.begin(), expected.end());
}

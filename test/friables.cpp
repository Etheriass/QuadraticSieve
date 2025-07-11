#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <utility> 
#include "../src/Eratosthene/eratosthene.hpp"
#include "../src/Friables/friables.hpp"


TEST(QBFriableTest, N2041) {
    std::vector<int> primes = eratosthene_sieve(8);
    std::pair<std::vector<__uint128_t>, std::vector<__uint128_t>> QfX = Q_B_friables_128(2041, 100, primes);
    std::vector<__uint128_t> Qf = QfX.first;
    std::vector<__uint128_t> X = QfX.second;
    std::vector<__uint128_t> expected_Qf = { 75, 168, 360, 560, 768, 875, 1323, 1440, 1680, 3000, 3584, 3888, 4200, 5184, 5880, 9408, 12600, 15120, 17280};
    std::vector<__uint128_t> expected_X = { 46, 47, 49, 51, 53, 54, 58, 59, 61, 71, 75, 77, 79, 85, 89, 107, 121, 131, 139};
    EXPECT_EQ(Qf, expected_Qf);
    EXPECT_EQ(X, expected_X);
}


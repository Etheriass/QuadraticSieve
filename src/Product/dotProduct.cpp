#include <vector>
#include <stdexcept>
#include "dotProduct.hpp"

int dot_product(std::vector<int> &a, std::vector<int> &b){
    if (a.size() != b.size()){
        throw std::invalid_argument("Dot product: vectors should have the same size");
        return 0;
    }
    int res = 0;
    for (int i = 0; i < a.size(); i++){
        res += a[i]*b[i];
    }
    return res;
}
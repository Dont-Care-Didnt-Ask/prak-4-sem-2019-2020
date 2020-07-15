#include <iostream>
#include <stdexcept>
#include <cstdint>

// Implement hyperoperation function, not using the 'return' operator.

struct Result{
    int64_t val_;
    Result(int64_t val = 0): val_(val){}
};

// Hyperoperation function
// (A way of extending binary operations beyond addition, multiplication and exponentiation)
void func(int64_t a, int64_t b, uint32_t k){
    if (k == 0) {
        throw Result{a + b};
    }
    else if (b == 1) {
        throw Result{a};
    }
    else {
        Result tmp;
        try {
            func(a, b - 1, k);
        } catch (const Result& res){
            tmp = res;
        }

        try {
            func(a, tmp.val_, k-1);
        } catch (const Result& res) {
            throw;
        }
    }
}

int main(){
    int64_t a, b;
    uint32_t k;
    while (std::cin >> a >> b >> k) {
        try {
            func(a, b, k);
        } catch (const Result& res){
            std::cout << res.val_ << std::endl;
        }
    }
}
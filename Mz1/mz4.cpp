#include <iostream>
#include <iomanip>
#include <cmath>

int main(){
    int cnt = 0;
    double cur = 0, sum = 0, sum_square = 0;
    while(std::cin >> cur) {
        cnt++;
        sum += cur;
        sum_square += cur * cur;

    }
    double mean = sum / cnt;
    double SD = sqrt((sum_square + cnt * mean * mean - 2 * sum * mean)/cnt);
    std::cout << std::fixed;
    std::cout << std::setprecision(10) << mean << std::endl;
    std::cout << std::setprecision(10) << SD << std::endl;
    return 0;
}
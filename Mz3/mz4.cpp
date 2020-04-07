#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

struct Mean
{
    double value = 0;
    int amount = 0;

    Mean(): value(0), amount(0) {}

    void operator ()(double n) {
        value += n;
        amount++;
    }
    double get() const {
        return value / amount;
    }
};


int main(){
    double num;
    std::vector<double> results;

    while(std::cin >> num){
        results.push_back(num);
    }
        
    int bound = results.size() / 10;
    if (bound > 0){
        auto first = results.begin();
        auto last = first + bound;
        results.erase(first, last);
        
        first = results.end();
        last = first - bound;
        results.erase(last, first);
    }

    std::sort(results.begin(), results.end());
    bound = results.size() / 10;
    if (bound > 0) {    
        // there is actually no need to erase elements this time, but anyway
        auto first = results.begin();
        auto last = first + bound;
        results.erase(first, last);
        first = results.end();
        last = first - bound;
        results.erase(last, first);
    }

    Mean answer = std::for_each(results.begin(), results.end(), Mean());
    std::cout << std::setprecision(10) << answer.get() << std::endl;
    return 0;
}
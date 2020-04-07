#include <iostream>
#include <string>
#include <vector>

#include "cmc_complex.h"
#include "cmc_complex_stack.h"
#include "cmc_complex_eval.h"

int main(int argc, char **argv){
    using namespace numbers;
    complex C(argv[1]);
    double R;
    std::istringstream(argv[2]) >> R;

    int N;
    std::istringstream(argv[3]) >> N;

    std::vector<std::string> function;
    for(int i = 4; i < argc; i++){
        function.push_back(argv[i]);
    }
    
    complex sum(0,0);

    double prev_angle = 0.0;
    complex prev = complex(R, 0);

    for (int i = 0; i < N; i++){
        // actually using M_PI is not recommended, 
        // but for some reason Chernoff rejects 'const double PI = 3.1415...' or 'const double PI = atan(1.) * 4;'
        double next_angle = 2.0 * M_PI * (i + 1) / N;
        double intermed_angle = (prev_angle + next_angle) / 2.0;

        complex next(R * cos(next_angle), R * sin(next_angle));
        complex intermed(R * cos(intermed_angle), R * sin(intermed_angle));
        
        complex point = C + intermed;
        complex current_val = eval(function, point);
        
        sum += current_val * (next - prev);
        prev_angle = next_angle;
        prev = next;
    }
    std::cout << sum.to_string() << std::endl;
    return 0;
}
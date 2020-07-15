#include <iostream>
#include <stdexcept>

/*
 * You are given a sequence of string, separated by 
 * whitespace characters. You have to output this sequence
 * in reversed order, i.e. given "abc bcd cde", you
 * have to print "cde bcd abc". The << operator can be used
 * only in the destructor of an auxilary class.
*/

class Auxilary{
    std::string str_;
public:
    Auxilary(const std::string& str): str_(str) {}
    ~Auxilary(){
        std::cout << str_ << std::endl;
    }
};

void tnirp(){
    std::string input;
    try {
        if (std::cin >> input) {
            Auxilary obj{std::move(input)};
            tnirp();
        } else {
            throw 1;
        }
    } catch (int) {
        throw;
    }
}

int main(){
    try {
        tnirp();
    } catch (int) {
    }
    return 0;
}

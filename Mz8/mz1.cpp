#include <iostream>
#include <string>

bool check(const std::string& str) {
    auto it = str.begin();
    
    while (it != str.end() && 
            (*it == '3' || *it == '4')) {
        ++it;
    }
    while (it != str.end() && 
            (*it == '1' || *it == '2')) {
        ++it;
    }
    return it == str.end();
}

int main() {
    std::string str;

    while (std::cin >> str) {
        std::cout << check(str) << std::endl;
    }
    
    return 0;
}

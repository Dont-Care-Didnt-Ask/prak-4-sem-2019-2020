#include <iostream>
#include <cctype>

bool check() {
    char sym;
    // skip spaces
    while (std::cin.get(sym) && isspace(static_cast<int>(sym)));

    size_t nulls = 0, ones = 0;
/*
    I increment 'nulls' and 'ones' in loop condition 
    since I have to get a new symbol after incrementing 
    and I don't want to make an extra 'if' in the loop body 
    to check if the read was successful.
*/
    while (sym == '0' && ++nulls && std::cin.get(sym));
    while (sym == '1' && ++ones  && std::cin.get(sym));
    
    if (nulls == 0 || ones == 0) {
        // get to the next word
        while (!isspace(static_cast<int>(sym)) 
                && std::cin.get(sym));            
        return false;
    }
    
    if (isspace(static_cast<int>(sym)) || std::cin.eof()) {
        return true;
    }

    while (true) {
        size_t null_cnt = nulls, one_cnt = ones;

        while (sym == '0' && null_cnt-- && std::cin.get(sym));
        while (sym == '1' && one_cnt--  && std::cin.get(sym));

        if (one_cnt || null_cnt) {
            // get to the next word
            while (!isspace(static_cast<int>(sym)) 
                    && std::cin.get(sym));
            return false;
        }

        if (isspace(static_cast<int>(sym)) || std::cin.eof()) {
            return true;
        }
    }
}

int main() {
    do {
        std::cout << check() << std::endl;
    } while (!std::cin.eof());
    
    return 0;
}


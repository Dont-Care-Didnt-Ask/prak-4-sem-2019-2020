#include <iostream>

/*
 * Recursive Descent Grammar:
 * S -> aAd
 * A -> aAd
 * A -> bBc
 * B -> bBc
 * B -> _
*/

void B (int k) {
    if (k >= 2) {
        std::cout << 'b';
        B(k-2);
        std::cout << 'c';
    }
}

void A (int k, int repeat) {
    if (repeat > 0) {
        std::cout << 'a';
        A(k-2, repeat - 1);
        std::cout << 'd';
    } else {
        std::cout << 'b';
        B(k-2);
        std::cout << 'c';
    }
}

void S (int k, int repeat) {
    if (k >= 4 && k % 2 == 0 && repeat > 0) {    
        std::cout << 'a';
        A(k-2, repeat - 1);
        std::cout << "d\n";
        S(k, repeat - 1);
    } 
}

int main() {
    int k;
    std::cin >> k;
    S(k, k / 2 - 1);
    return 0;
}
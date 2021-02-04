#include <iostream>

/*
 * L = { s: s = (a)^n (0)^m (b)^n (1)^m, m > 0, n > 0 }
 * Language is of type 1 (context-sensitive) since: 
 * 
 * 1) It does not satisfy the conditions of
 * pumping lemma for context-free languages.
 * https://en.wikipedia.org/wiki/Pumping_lemma_for_context-free_languages
 * 
 * For example, word s = (a)^p (0)^p (b)^p (1)^p 
 * can not be "pumped" into anything.
 *  We have to pump either (a) and (b) or (0) and (1)
 * simultaniosly, but we aren't able to do it due to the 
 * condition |vwx| < p.
 * 
 * 2) It can be generated with the following context-sensitive grammar:
 * 
 *  S -> LN
 *  L -> aLb | ab
 *  N -> QN1 | Q1
 *  bQ -> UQ
 *  UQ -> Qb
 *  aQ -> a0
 *  0Q -> 00
 */

int main() {
    std::string word;

    while (std::cin >> word) {
        auto it = word.begin();
        int letters = 0, numbers = 0;
    
        while (it != word.end() && *it == 'a') {
            ++letters;
            ++it;
        }
    
        while (it != word.end() && *it == '0') {
            ++numbers;
            ++it;
        }
    
        if (letters == 0 || numbers == 0) {
            std::cout << "0\n";
        } else {
            while (it != word.end() && *it == 'b') {
                --letters;
                ++it;
            }
    
            while (it != word.end() && *it == '1') {
                --numbers;
                ++it;
            }
    
            if (letters != 0 || numbers != 0 || it != word.end()) {
                std::cout << "0\n";
            } else {
                std::cout << "1\n";
            }
        }
    }
    
    return 0;
}
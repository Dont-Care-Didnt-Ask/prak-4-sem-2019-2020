#include <iostream>
#include <cctype>

/* I had two versions and I by now have no idea, which of them is correct.
 */

struct Properties {
    int len = 0;
    int nonterminals = 0;
    char first_nonterm = '\0';
    bool has_start_sym = false;
    bool empty = false;
    
    Properties(const std::string& str);
};

int main() {
    std::string rhs;
    char lhs;

    bool left_linear = true;
    bool right_linear = true;

    bool automatic = true;

    bool noncontracting = true;

    bool has_S_on_right = false;
    bool vanishing_S = false;
    bool S_to_nonterminal = false;
    
    while (std::cin >> lhs && std::cin >> rhs) {
        Properties second(rhs);

        if (second.empty) {
            if (lhs == 'S' && rhs == "_") {
                vanishing_S = true;
            } else {
                noncontracting = false;
            }
        }

        if (!has_S_on_right && second.has_start_sym) {
            has_S_on_right = true;
        }

        if (!S_to_nonterminal
                && lhs == 'S' 
                && second.len == 1 
                && second.nonterminals == 1) {

            S_to_nonterminal = true;
        }

        if (second.nonterminals > 1) {
            automatic = false;
            left_linear = false;
            right_linear = false;

        } else if (second.nonterminals == 1) {
            if (second.first_nonterm != rhs[0]) {
                left_linear = false;
            }
            if (second.first_nonterm != rhs[second.len - 1]) {
                right_linear = false;
            }
            if (second.len > 2) {
                automatic = false;
            } else if (second.len == 1 && lhs != 'S') {
                automatic = false;
            }

        } else {
            if (second.len > 1 ||
                    (second.empty && lhs != 'S')) {
                automatic = false;
            }
        }
    }

    if (vanishing_S && has_S_on_right) {
        noncontracting = false;
        automatic = false;
    }

    if (vanishing_S < S_to_nonterminal) {
        automatic = false;
    }

    if (left_linear || right_linear) {
        if (automatic) {
            if (left_linear) {
                std::cout << "311\n";
            } else {
                std::cout << "321\n";
            }
        } else {
            if (left_linear) {
                std::cout << "31\n";
            } else {
                std::cout << "32\n";
            }
        }
    } else {
        if (noncontracting) {
            std::cout << "21\n";
        } else {
            std::cout << "2\n";
        }
    }

    return 0;
}

Properties::Properties(const std::string& str) {
    len = str.size();
    for (char sym : str) {
        if (isupper(sym)) {
            nonterminals++;
            if (nonterminals == 1) {
                first_nonterm = sym;
            }
            if (sym == 'S') {
                has_start_sym = true;
            }
        } else if (sym == '_') {
            empty = true;
        }
    }
}
#include <iostream>
#include <cctype>
#include <algorithm>

struct Properties {
    int len = 0;
    int nonterminals = 0;
    bool has_start_sym = false;
    bool empty = false;
    bool invalid = false; // probably unneccessary
    
    Properties(const std::string& str);
};

Properties::Properties(const std::string& str) {
    len = str.size();
    for (auto sym : str) {
        if (isupper(sym)) {
            nonterminals++;

            if (sym == 'S') {
                has_start_sym = true;
            }
        } else if (sym == '_') {
            empty = true;
        } else if (!isalnum(sym)) {
            invalid = true;
        }
    }
}

int main() {
    std::string lhs, rhs;

    bool noncontracting = true;
    bool context_free = true;
    bool has_S = false;
    bool has_S_on_right = false;
    bool vanishing_S = false;
    
    while (std::cin >> lhs && std::cin >> rhs) {
        Properties first(lhs), second(rhs);

        if (first.nonterminals == 0
                || first.invalid
                || second.invalid
                || first.empty 
                || (second.empty && (second.len > 1))) {
            std::cout << "-1\n";
            return 0;
        }

        if (!has_S && lhs == "S") {
            has_S = true;
        }

        if (!has_S_on_right && second.has_start_sym) {
            has_S_on_right = true;
        }

        if (first.len > second.len || second.empty) {
            if (lhs == "S" && rhs == "_") {
                vanishing_S = true;
            } else {
                noncontracting = false;
            }
        }
        
        if (context_free && first.len > 1) {
            context_free = false;
        }
    }

    if (vanishing_S && has_S_on_right) {
        noncontracting = false;
    }

    if (has_S) {
        if (context_free) {
            if (noncontracting) {
                std::cout << "23\n";
            } else {
                std::cout << "2\n";
            }
        } else {
            std::cout << "10\n";
        }
    } else {
        std::cout << "-1\n";
    }

    return 0;
}

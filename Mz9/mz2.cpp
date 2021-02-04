#include <iostream>
#include <string>
#include <map>
#include <set>

struct Input {
    char state;
    char sym;

    explicit Input(char st, char s) : state(st), sym(s) {}

    friend std::ostream& operator<<(std::ostream& out, const Input& var) {
        out << '(' << var.state << ", " << var.sym << ')';
        return out;
    }
};

class Lex {
    const std::multimap<Input, char> transitions;
    std::set<char> state;

public:
    Lex(std::multimap<Input, char> table)
        : transitions{table}, state{'H'}
    {}

    void reset() {
        state = {'H'};
    }

    bool operator()(const std::string& str);
};

int main() {
    std::multimap<Input, char> transitions = {
        {Input('H', '0'), 'A'},
        {Input('H', '1'), 'A'},
        {Input('A', '1'), 'A'},
        {Input('A', '0'), 'A'},

        {Input('A', '1'), 'B'},
        {Input('H', '1'), 'B'},
        
        {Input('B', '0'), 'C'},
        {Input('B', '1'), 'C'},

        {Input('C', '1'), 'S'},
        {Input('C', '0'), 'S'},
    };

    Lex automata{std::move(transitions)};
    
    std::string input;
    while (std::cin >> input) {
        std::cout << automata(input) << '\n';
        automata.reset();
    }

    return 0;
}

bool Lex::operator()(const std::string& str) {
    auto head = str.begin();

    while (state.size() && head != str.end()) {
        std::set<char> new_state;

        for (char st : state) {
            const Input key(st, *head);
            auto range = transitions.equal_range(key);
            
            for (auto it = range.first; it != range.second; ++it) {
                new_state.insert(it->second);
            }
        }
        state = new_state;
        head++;
    }

    if (state.find('S') != state.end() && head == str.end()) {
        return true;
    }
    
    return false;
}

bool operator< (const Input lhs, const Input rhs) {
    return lhs.state < rhs.state || 
        (lhs.state == rhs.state && lhs.sym < rhs.sym);
}

bool operator== (const Input lhs, const Input rhs) {
    return !(lhs < rhs || rhs < lhs); 
}
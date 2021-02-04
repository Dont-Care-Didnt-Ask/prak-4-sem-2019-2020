#include <iostream>
#include <string>
#include <map>
#include <set>

struct Input {
    std::string state;
    char sym;

    explicit Input(const std::string& st, char s) : state(st), sym(s)
    {}
};

struct Answer {
    int steps_;
    std::string state_;
    bool belongs_;

    explicit Answer(int steps, std::string state, bool belongs)
        : steps_{steps}, state_{state}, belongs_{belongs}
    {}

    friend std::ostream& operator<< (std::ostream& out, Answer var) {
        out << var.belongs_ << '\n' << var.steps_ << '\n' << var.state_;
        return out;
    }
};

class DFA {
    const std::map<Input, std::string> transitions;
    const std::set<std::string> stop_states;
    std::string state;

public:
    explicit DFA(std::map<Input, std::string>&& table, 
            std::set<std::string>&& stopping, 
            std::string&& start)
        : transitions{table}, stop_states{stopping}, state{start}
    {}
    
    Answer operator()(const std::string& str);
};

int main() {
    std::map<Input, std::string> transitions;
    std::set<std::string> stopping;
    std::string cur, next;
    const std::string delim{"END"};
    char sym;

    while (std::cin >> cur && cur != delim) {
        std::cin >> sym >> next;
        transitions.emplace(Input(cur, sym), next);
    }

    while (std::cin >> cur && cur != delim) {
        stopping.emplace(cur);
    }
    
    std::cin >> cur;
    DFA automata{std::move(transitions), std::move(stopping), std::move(cur)};
    
    std::string input;
    std::cin >> input;

    std::cout << automata(input) << std::endl;
    
    return 0;
}

Answer DFA::operator()(const std::string& str) {
    auto head = str.begin();
    int cnt = 0;
    std::map<Input, std::string>::const_iterator it;
    auto end = transitions.end();

    while (head != str.end() && (it = transitions.find(Input(state, *head))) != end) {
        state = it->second;
        ++cnt;
        ++head;
    }

    if (head == str.end() && stop_states.find(state) != stop_states.end()) {
        return Answer(cnt, state, 1);
    }
    
    return Answer(cnt, state, 0);
}

bool operator< (const Input lhs, const Input rhs) {
    return lhs.state < rhs.state || 
        (lhs.state == rhs.state && lhs.sym < rhs.sym);
}
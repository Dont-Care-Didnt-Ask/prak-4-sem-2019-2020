#include <iostream>
#include <string>
#include <map>

/*
 * This is an implementation of Turing machine.
 * The main idea is to use std::map to represent the set of rules.
*/

struct Input
{
    char state;
    char read_sym;

    Input(char st, char s) : state(st), read_sym(s)
    {}
};
// this operator is needed for ordering inside std::map
bool operator< (const Input lhs, const Input rhs) {
    return lhs.state < rhs.state || 
        (lhs.state == rhs.state && lhs.read_sym < rhs.read_sym);
}

struct Output
{
    char state;
    char sym;
    char move;

    Output(char st, char s, char m) : state(st), sym(s), move(m)
    {}
};

bool operator< (const Output lhs, const Output rhs) {
    return lhs.state < rhs.state || 
        (lhs.state == rhs.state && lhs.sym < rhs.sym) || 
        (lhs.state == rhs.state && lhs.sym == rhs.sym && lhs.move < rhs.move);
}

class TM
{
    std::map<Input, Output> rules;
    char state = 'S';
public:
    TM(std::map<Input, Output> table);
    std::string& operator()(std::string& str);
};

int main() {
    std::map<Input, Output> rules = {
        {Input('S', '0'), Output('S', '0', 'R')},
        {Input('S', '1'), Output('A', '1', 'R')},
        {Input('S', '#'), Output('S', '#', 'R')},

        {Input('A', '0'), Output('A', '0', 'R')},
        {Input('A', '1'), Output('S', '1', 'R')},
        {Input('A', '#'), Output('B', '#', 'L')},

        {Input('B', '0'), Output('B', '0', 'L')},
        {Input('B', '1'), Output('B', '1', 'L')},
        {Input('B', '#'), Output('C', '#', 'R')},

        {Input('C', '0'), Output('C', '0', 'R')},
        {Input('C', '1'), Output('D', '0', 'S')},

        {Input('D', '0'), Output('D', '0', 'S')}
    };
    TM machine{std::move(rules)};
    
    std::string input;
    std::cin >> input;

    std::cout << machine(input) << std::endl;
    
    return 0;
}


TM::TM(std::map<Input, Output> table): rules(table), state('S')
{}

std::string& TM::operator()(std::string& str)
{
    auto head = str.begin();
    // 'H' stands for 'halt' - stopping state
    while (state != 'H' && head != str.end()) {
        auto it = rules.find(Input(state, *head));

        if (it == rules.end()) {
            state = 'H';
            
        } else {
            Output& cur = it->second;

            state = cur.state;
            *head = cur.sym;
            if (cur.move == 'R') {
                head++;
            } else if (cur.move == 'L') {
                if (head == str.begin()) { // falls off the tape
                    state = 'H';
                } else {
                    head--;
                }
            } else {
                state = 'H';
            }
        }
    }
    return str;
}
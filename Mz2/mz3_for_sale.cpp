#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace numbers 
{
    // Define a few function types
    typedef complex(*complex_binary_operation_t)(complex, complex);
    typedef complex(*complex_unary_operation_t)(complex);
    typedef complex_stack(*stack_operation_t)(complex_stack);

    complex eval(const std::vector<std::string> &args, const complex &z) {
        using std::map;
        using std::string;
        using std::vector;

        // Connect each sign to a function
        map <string, complex_binary_operation_t> bin_actions{
            {"+", [](complex a, complex b)-> complex { return a + b; }},
            {"-", [](complex a, complex b)-> complex { return a - b; }},
            {"*", [](complex a, complex b)-> complex { return a * b; }},
            {"/", [](complex a, complex b)-> complex { return a / b; }}
        };
        
        map <string, complex_unary_operation_t> un_actions {
            {"~", [](complex a)->complex{ return ~a; }},
            {"#", [](complex a)->complex{ return -a; }}
        };

        map <string, stack_operation_t> stack_actions{
            {"!", [](complex_stack st)->complex_stack{ return st << +st; }},
            {";", [](complex_stack st)->complex_stack{ return ~st;}}
        };
        
        complex_stack my_stack;
        
        // range-based loop
        for (const string& elem : args) {
            auto bin_it = bin_actions.find(elem);
            auto un_it  = un_actions.find(elem);
            auto st_it  = stack_actions.find(elem);

            if (bin_it != bin_actions.end()) {
                complex second = +my_stack;
                my_stack = ~my_stack;
                complex first = +my_stack;
                my_stack = ~my_stack;
                my_stack = my_stack << (bin_actions[bin_it->first](first, second));
                
            } else if (un_it != un_actions.end()){
                complex last = +my_stack;
                my_stack = ~my_stack;
                my_stack = my_stack << (un_actions[un_it->first](last));

            } else if (st_it != stack_actions.end()) {
                my_stack = stack_actions[st_it->first](my_stack);
            } else if (elem == "z") {
                my_stack = my_stack << z;
            } else {
                my_stack = my_stack << complex(elem);
            }
        } // for ends
        return +my_stack;
    }
} // namespace numbers

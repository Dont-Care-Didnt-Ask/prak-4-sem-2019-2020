#include <iostream>

/*
 * Define a class, which contains an integer, has a
 * move-constructor and an operator of conversion to bool.
 * The following code

void func(S object) {
    if (object) {
        func(std::move(object));
    }
}
int main() {
    func(S{});
    return 0;
}

 * should output the sum of numbers if the input is not empty
 * and nothing (not even a ' ' or '\n') otherwise.
 * For example, you should print "10", given "1 2 3 4" or "10".
*/

class S {
    int val_;
    bool print;

public:
    S() {
        print = bool(std::cin >> val_);
    }

    S (S&& other): val_{other.val_} {
        int tmp;
        print = bool(std::cin >> tmp);
        if (print) {
            other.print = false;
            val_ += tmp;
        }
    }

    ~S() {
        if (print) {
            std::cout << val_ << std::endl;
        }
    }

    operator bool() const{
        return print;
    }
};
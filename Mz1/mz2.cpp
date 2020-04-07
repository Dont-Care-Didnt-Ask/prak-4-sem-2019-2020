#include <iostream>

class A {
    int a = 0;
    bool flg_copy = false;
public:
    A(){
        std::cin >> a;
    }
    A(const A& var): flg_copy{true} {
        std::cin >> a;
        a += var.a;        
    }
    ~A() {
        if(flg_copy){
            std::cout << a << std::endl;
        }
    }
};

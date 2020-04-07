#include <cstdint>

class Sub {
    int a_, b_;
public:
    Sub(int a = 0, int b = 0): a_(a), b_(b)
    {}
    
    Sub (const Sub& var1, const Sub& var2): a_(var1.value()), b_(var2.value())
    {}
    
    int value() const {
        return a_ - b_;
    }
};

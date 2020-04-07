#include <cstdint>

class Sum {
    int64_t a_, b_;
public:
    Sum (int64_t a, int64_t b): a_(a), b_(b)
    {}
    
    Sum (const Sum& var, int64_t c): a_(var.get()), b_(c)
    {}
    
    int64_t get() const {
        return a_ + b_;
    }
};

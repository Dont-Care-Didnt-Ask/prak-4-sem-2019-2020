#include <iostream>

namespace numbers{
    class complex_stack{
        size_t allocated_, top_;
        complex *stack_;
        
        complex_stack(size_t sz, size_t top, complex *arr): allocated_(sz), top_(top) {
            //std::cout << "Created stack with size " << sz << " and " << top << " values\n";
            if (arr) {
                stack_ = arr;
            } else {
                stack_ = new complex[sz];
            }
        }
    public:
        complex_stack(size_t sz = 1): allocated_(sz), top_(0) {
            //std::cout << "Default creat\n";
            stack_ = static_cast<complex*>(::operator new (sizeof(*stack_) * sz));
        }

        // copy-constructor
        complex_stack(const complex_stack& other): allocated_(other.allocated_), top_(other.top_) {
            //std::cout << "Copied stack with size " << other.allocated_ << " and top " << other.top_ <<  "\n";

            stack_ = static_cast<complex*>(::operator new (sizeof(*stack_) * other.allocated_));
            for (size_t i = 0; i < top_; i++) {
                new (stack_ + i) complex(other.stack_[i]);
            }
        }
        
        // move-constructor
        complex_stack(complex_stack&& other): allocated_(other.allocated_), top_(other.top_), stack_(other.stack_) {
            //std::cout << "Moving stack with size " << other.allocated_ << " and top " << other.top_ <<  "\n";
            other.allocated_ = 0;
            other.top_ = 0;
            other.stack_ = nullptr;
        }
        
        // destructor
        ~complex_stack(){
            //std::cout << "Destructed stack, size " << allocated_ << "\n";
            for (size_t i = 0; i < top_; i++)
            {
                stack_[i].~complex();
            }
            ::operator delete(stack_);
        }

        void swap(complex_stack&& other) {
            std::swap(stack_, other.stack_);
            std::swap(top_, other.top_);
            std::swap(allocated_, other.allocated_);
        }
        
        // copy-and-swap assignment
        // takes a reference and makes a copy inside, otherwise it conflicts with move assignment
        complex_stack& operator = (const complex_stack& other){ 
            //std::cout << "Swap= stack with size " << other.allocated_ << " and top " << other.top_ <<  "\n";
            swap(complex_stack(other));
            return * this;
        }
        
        // move assignment
        complex_stack& operator = (complex_stack&& other) {
            //std::cout << "Move= stack with size " << other.allocated_ << "\n";
            swap(std::move(other));
            return *this;
        }
        
        // function-members
        size_t size() const { return top_; }

        const complex operator [](const size_t idx) const{
            return stack_[idx];
        }
        complex_stack operator << (const complex num) const{
            
            //std::cout << " Pushing " << num << ": old top = " << top_ << ", old size = " << allocated_ << "\n";
            size_t sz = (top_ >= allocated_) ? 2*allocated_ : allocated_;
            complex *arr = static_cast<complex*>(::operator new (sizeof(*arr) * sz));
            for (size_t i = 0; i < top_; i++)
            {
                new (arr + i) complex(stack_[i]);
            }
            new (arr + top_) complex(num);

            return complex_stack(sz, top_ + 1, arr);
        }
        
        complex_stack operator ~ () const{
            complex_stack tmp(*this);
            tmp.top_--;
            return tmp;
        }

        complex operator + () const {
            return stack_[top_-1];
        }
        friend std::ostream& operator <<(std::ostream& s, const complex_stack& st);
    };

    std::ostream& operator <<(std::ostream& s, const complex_stack& st){
        for (size_t i = 0; i < st.size(); i++)
        {
            std::cout << st[i] << " ";
        }
        std::cout << std::endl;
        return s;
        
    }
}

int main(){
    using namespace numbers;
    complex x1{1,0}, x2(2), x3(3,0), x4(4), x5("(5,5)");
    const complex x6{6,0};
    complex_stack my_stack;

    my_stack = my_stack << x1 << x2 << x3 << x6;
    //std::cout << my_stack;
    //std::cout << my_stack[idx] << "\n";
    //std::cout << (my_stack << x6);
    //std::cout << my_stack.size();

    //my_stack[idx] = x1;
    
    [[maybe_unused]] auto sum = [](complex a, complex b)->complex{ return a + b;};
    [[maybe_unused]] complex(*mul)(complex, complex) = [](complex a, complex b)-> complex {return a * b;};
    
    while (my_stack.size() > 1) {
        std::cout << my_stack;
        complex last = +my_stack;
        my_stack = ~my_stack;
        std::cout << my_stack;
        complex second_to_last = +my_stack;
        my_stack = ~my_stack;
        std::cout << my_stack;
        my_stack = my_stack << sum(last, second_to_last);
    }
    std::cout << +my_stack << "\n";

/*
    complex_stack one;
    one = one << x1 << x2 << x3 << x4;
    std::cout << one.size() << std::endl;
    numbers::complex_stack two;
    two = one;
    std::cout << +one << "\n";
    std::cout << one[0] << one[1] << one[2] << one[3] << "\n";
    std::cout << two[0] << two[1] << two[2] << two[3] << std::endl;
    one = ~one;

    std::cout << one[0] << one[1] << one[2] << "\n";
    std::cout << two[0] << two[1] << two[2] << two[3] << "\n";
    one = ~two;

    std::cout << one[0] << one[1] << one[2] << "\n";
    std::cout << two[0] << two[1] << two[2] << two[3] <<"\n";

    one = one << x5;
    
    std::cout << one[0] << one[1] << one[2] << one[3] << "\n";
    std::cout << two[0] << two[1] << two[2] << two[3] << "\n";

    one = ~one << x1;
    std::cout << one[0] << one[1] << one[2] << one[3] << std::endl;
    */
    //std::cout << two[0] << two[1] << "\n";
    //std::cout << three[0] << " " << three[1] << " " << three[2] << "\n";
    //std::cout << +two << "\n";
    //std::cout << +new_two << "\n";
    //std::cout << +one << "\n";


    return 0;
}

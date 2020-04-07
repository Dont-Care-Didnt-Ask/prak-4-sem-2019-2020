#include <string>

class Figure{
public:
    virtual double get_square() const = 0;
    virtual std::string to_string() const = 0;
    virtual ~Figure(){}
};
/*
In every abstract class we must have virtual destructor
to destroy objects correctly no matter what
Imagine a programm:

int main(){
    class Figure{...};

    class Square : public Figure {...};

    Figure * ptr = new Square{};
    ...
    delete ptr;
}

If we don't have a virtual destructor, only a ~Figure() will be called.
If we make a dynamic allocation somewhere inside Square{}, like
... 
    Square(int side): side_{side} {
        int my_ptr = new int;
    }
    ~Square(){
        delete my_ptr;
    }
...
we will get a memory leak, since ~Square() is never called.
*/
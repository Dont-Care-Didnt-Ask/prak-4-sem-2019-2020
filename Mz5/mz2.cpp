#include <cmath>
#include <string>
#include <sstream>
//#include "mz05-1.cpp"

class Rectangle : public Figure{
    double width_, height_;
public:
    Rectangle(std::string str){
        std::istringstream(str) >> width_ >> height_;
    }
    static Rectangle * make(std::string str){
        return new Rectangle{str};
    }
    virtual double get_square() const {
        return width_ * height_;
    }
    std::string to_string() const {
        std::ostringstream out;
        out << "R " << width_ << " " << height_ << "\n";
        return out.str();
    }
};

class Square : public Figure{
    double side_;
public:
    Square(std::string str){
        std::istringstream(str) >> side_;
    }
    static Square *make(std::string str){
        return new Square{str};
    }
    virtual double get_square() const {
        return side_ * side_;
    }
    std::string to_string() const {
        std::ostringstream out;
        out << "S " << side_ << "\n";
        return out.str();
    }
};

class Circle : public Figure{
    double radius_;
public:
    Circle(std::string str){
        std::istringstream(str) >> radius_;
    }
    static Circle *make(std::string str){
        return new Circle{str};
    }
    virtual double get_square() const {
        return M_PI * radius_ * radius_;
    }
    std::string to_string() const {
        std::ostringstream out;
        out << "C " << radius_ << "\n";
        return out.str();
    }
};
/*
Complex number class realization

*/

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

namespace numbers {
    class complex
    {
        double re_ = 0, im_ = 0;

    public:
        /* 
        parametrized constructor
        can't write im_(i), re_(r) - the order is important
         */
        complex (double r = 0, double i = 0): re_(r), im_(i) {}

        // copy constructor
        complex (const complex &c): re_(c.re_), im_(c.im_) {}

        /*
        another parametrized constructor
            complex a;
            std::string str = "(0,0)";
            a = str;            // error, since the constructor is 'explicit'
            a = complex(str);   // success
        */
        explicit complex (const std::string& str) {
            std::stringstream s(str);
            char c;
            s >> c >> re_ >> c >> im_;
        }
        // function-members
        double abs() const {
            return sqrt(re_ * re_ + im_ * im_);
        }
        double abs2() const {
            return (re_ * re_ + im_ * im_);
        }

        double re() const { return re_;}
        double im() const { return im_;}
        
        const std::string to_string() const {
            std::stringstream s;
            s << "(" << std::setprecision(10) << re_ << "," << im_ << ")";
            /*
            We create a stream object, write down the output, like we do
            with std::cout, and than convert it to a string
            */
            return s.str();
        }

        /*
        Taking argument 'c' by constant reference instead of reference allows us to write
            complex a{};
            int num = 5;
            a = num;    // now a equals (5, 0), since 'int' can be implicitly converted to 'const complex&'
        */
        complex& operator = (const complex &c) 
        {
            re_ = c.re_;
            im_ = c.im_;
            return *this;
        }

        complex& operator += (const complex &c)   
        {
            re_ += c.re_;
            im_ += c.im_;
            return *this;
        }
        complex& operator -= (const complex &c)   
        {
            re_ -= c.re_;
            im_ -= c.im_;
            return *this;
        }
        complex& operator *= (const complex &c)   
        {
            complex tmp = complex((c.re_ * re_ - c.im_ * im_), (c.im_ * re_ + c.re_ * im_));
            re_ = tmp.re_;
            im_ = tmp.im_;
            return *this;
        }
        complex& operator /= (const complex &c)   
        {
            double r = c.abs2();
            complex tmp = complex( (re_ * c.re_ + im_ * c.im_) / r, (im_ * c.re_ - re_ * c.im_) / r);
            re_ = tmp.re_;
            im_ = tmp.im_;
            return *this;
        }
        
        complex operator - () const { return complex(-re_, -im_); }
        complex operator ~ () const { return complex(re_, -im_); }
    };

    /*
    The functions below are outside the class
    That's why we have to take two arguments - we don't have implicit argument 'this'
    Example:
        complex a, b;
        int num;

        a + b; // correct
        a + num; // correct
        num + a; // correct. Wouldn't have worked, if operator + was defined in class.
    */

    // Btw, we are reusing the implementation of +=, -=, *= and /=
    inline complex operator + (complex c1, complex c2) {
        return c1 += c2;
    }
    inline complex operator - (complex c1, complex c2) {
        return c1 -= c2;
    }
    inline complex operator * (complex c1, complex c2) {
        return c1 *= c2;
    }
    inline complex operator / (complex c1, complex c2) {
        return c1 /= c2;
    }

}
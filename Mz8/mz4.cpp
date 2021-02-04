#include <iostream>
#include <exception>
#include <type_traits>
#include <limits>
#include <sstream>

template <typename T>
class Range {
    T low, high;

    // don't be afraid, it's just a string parser
    static std::pair<std::string, std::string> parser(const std::string& str) {
        auto it = str.begin();
        auto end = str.end();

        if (it != end && *it == '(') {  // check for opening bracket
            ++it;
        } else {
            throw std::invalid_argument("Invalid input\n");
        }
        
        auto first_beg = it;
        
        if (it != end && (*it == '+' || *it == '-')) {  // sign check (optional)
            ++it;
        }

        while (it != end && isdigit(*it)) { // go through first number
            ++it;
        }

        auto first_end = it;
        
        if (it != end && *it == ',') {  // check for comma
            ++it;
        } else {
            throw std::invalid_argument("Invalid input\n");
        }

        // skip spaces (which shouldn't be here according to
        // the tasks, but se la vi)
        while (it != end && isspace(*it)) { 
            ++it;
        }

        auto second_beg = it;
        
        if (it != end && (*it == '+' || *it == '-')) {   // sign check
            ++it;
        }

        while (it != end && isdigit(*it)) { // go through second number
            ++it;
        }
        
        auto second_end = it;
        
        if (it == end || *it != ')' || ++it != end) {   // we should end up on closing bracket
            throw std::invalid_argument("Invalid input\n");
        }
        
        std::string l(first_beg, first_end);
        std::string r(second_beg, second_end);
        return {l, r};
    }

public:
    Range(T left = T{}, T right = T{}) {
        static_assert(std::is_class_v<T> || (std::is_integral_v<T> && std::is_signed_v<T>),
                "Can't handle this type");
        
        low = left;
        high = right;

        if (high < low) {
            throw std::invalid_argument("'low' is greater than 'high'");
        }
    }

    explicit Range(const std::string& str) {
        static_assert(std::is_class_v<T> || (std::is_integral_v<T> && std::is_signed_v<T>),
                "Can't handle this type");

        if constexpr (std::is_integral_v<T> && std::is_signed_v<T>) {

            auto [l_str, r_str] = parser(str);

            long long low_buf, high_buf;

            if ( ! (std::istringstream(l_str) >> low_buf 
                    && std::istringstream(r_str) >> high_buf)) {

                throw std::range_error("Type limits exceeded\n");
            }
            
            low = low_buf;
            high = high_buf;
            
            if (low != low_buf || high_buf != high) {
                throw std::range_error("Type limits exceeded\n");
            }

            if (low > high) {
                throw std::invalid_argument("'low' is greater than 'high'\n");
            }
        } else {                    // user-defined type
            auto [l_str, r_str] = parser(str);

            low = T(l_str);
            high = T(r_str);

            if (high < low) {
                throw std::invalid_argument("'low' is greater than 'high'\n");
            }
        }
    }

    std::string to_string() const;
    
    T get_low() const {
        return low;
    }
    
    T get_high() const {
        return high;
    }
    
    Range operator- () const;
};


template <typename T>
std::string Range<T>::to_string() const {
    std::ostringstream out;
    
    if constexpr (std::is_class_v<T>) {     // if type is user-defined
        out << "(" << low << "," << high << ")";
    } else {
        out << "(" << (long long)low << "," << (long long)high << ")";
    }

    return out.str();
}

template <typename T>
Range<T> Range<T>::operator- () const {
    if constexpr (std::is_integral_v<T> && std::is_signed_v<T>) {
        if (low == std::numeric_limits<T>::min()) {
            throw std::overflow_error("Overflow while negating");
        }
    }

    return Range<T>((T)(-high), (T)(-low));
}

template <typename T>
Range<T> operator +(const Range<T>& lhs, const Range<T>& rhs) {
    T low = lhs.get_low();
    T high = lhs.get_high();
    T other_low = rhs.get_low();
    T other_high = rhs.get_high();

    if constexpr (std::is_integral_v<T> && std::is_signed_v<T>) {
        if (__builtin_add_overflow_p(low, other_low, low)
                || __builtin_add_overflow_p(high, other_high, high)) {
            throw std::overflow_error("Overflow while adding\n");
        }
    }

    return Range<T>((T)(low + other_low), (T)(high + other_high));
}

template <typename T>
Range<T> operator +(const Range<T>& lhs, T rhs) {
    return lhs + Range<T>{rhs};
}

template <typename T>
Range<T> operator +(T lhs, const Range<T>& rhs) {
    return Range<T>{lhs} + rhs;
}

template <typename T>
Range<T> operator -(const Range<T>& lhs, const Range<T>& rhs) {
    T low = lhs.get_low();
    T high = lhs.get_high();
    T other_low = rhs.get_low();
    T other_high = rhs.get_high();

    if constexpr (std::is_integral_v<T> && std::is_signed_v<T>) {
        if (__builtin_sub_overflow_p(low, other_high, low)
                || __builtin_sub_overflow_p(high, other_low, high)) {
            throw std::overflow_error("Overflow while substracting\n");
        }
    }
    return Range<T>((T)(low - other_high), (T)(high - other_low));
}

template <typename T>
Range<T> operator -(const Range<T>& lhs, T rhs) {
    return lhs - Range<T>{rhs};
}

template <typename T>
Range<T> operator -(T lhs, const Range<T>& rhs) {
    return Range<T>{lhs} - rhs;
}

template <typename T>
Range<T> operator *(const Range<T>& lhs, const Range<T>& rhs) {
    T low = lhs.get_low();
    T high = lhs.get_high();
    T other_low = rhs.get_low();
    T other_high = rhs.get_high();

    if constexpr (std::is_integral_v<T> && std::is_signed_v<T>) {
        if (__builtin_mul_overflow_p(low, other_low, low)
                || __builtin_mul_overflow_p(low, other_high, low)
                || __builtin_mul_overflow_p(high, other_low, low)
                || __builtin_mul_overflow_p(high, other_high, low)) {
            throw std::overflow_error("Overflow while multiplying\n");
        }
    }
    T ll = low * other_low;
    T lh = low * other_high;
    T hl = high * other_low;
    T hh = high * other_high;

    T max = std::max(std::max(ll, lh), std::max(hl, hh));
    T min = std::min(std::min(ll, lh), std::min(hl, hh));
    return Range<T>(min, max);
}

template <typename T>
Range<T> operator *(const Range<T>& lhs, T rhs) {
    return lhs * Range<T>{rhs};
}

template <typename T>
Range<T> operator *(T lhs, const Range<T>& rhs) {
    return Range<T>{lhs} * rhs;
}
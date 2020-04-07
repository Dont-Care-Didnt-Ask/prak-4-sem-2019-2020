#include <functional>
#include <vector>
#include <iterator>

template <class It_t, class Func_t>
void myapply(It_t first, It_t last, Func_t func)
{
    for (auto it = first; it != last; ++it){
        func(*it);
    }
}

template <class It_t, class Func_t>
auto myfilter2(It_t first, It_t last, Func_t pred)
{
    // iterator_traits is needed to process C arrays
    // reference_wrapper is needed to to store references in a vector
    std::vector<typename std::reference_wrapper<typename std::iterator_traits<It_t>::value_type>> filtered{};
    
    for (auto it = first; it != last; ++it) {
        if (pred(*it)) {
            filtered.emplace_back(std::ref(*it));
        }
    }
    return filtered;
}
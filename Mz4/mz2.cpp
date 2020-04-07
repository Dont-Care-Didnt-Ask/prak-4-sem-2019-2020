#include <functional>

template <class T>
auto myfilter(const T& cont, std::function<bool (typename T::value_type)> pred) -> T
{
    T filtered{};
    for (const auto x: cont){
        if (pred(x)) {
            filtered.insert(filtered.end(), x);
        }
    }
    return filtered;
}
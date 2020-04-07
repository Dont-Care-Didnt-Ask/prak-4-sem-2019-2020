template<typename T>
auto process(const T& cont) -> typename T::value_type
{
    typename T::value_type sum{};

    typename T::const_reverse_iterator it = cont.rbegin();
    int pos = 0;
    while (it != cont.rend() && pos < 5) {
        if (pos % 2 == 0) {
            sum += *it;
        }
        ++pos;
        ++it;
    }
    return sum;
}

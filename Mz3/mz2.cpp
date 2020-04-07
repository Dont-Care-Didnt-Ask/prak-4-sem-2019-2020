#include <vector>
#include <cstdint>

void process(std::vector<int64_t>& vec, int64_t threshold){
    /*
    One does not simply write 'vec.push_back(...)'
    because if vector's capacity is not enough, it will be resized
    and all iterators will become invalidated, including 'it', which we use in 'for' loop.
    This can consequnce in big bad undefined behaviour.
    Or, even worse, you can get reject.
    */
    size_t expansion = 0;
    for (auto el : vec) {
        if (el >= threshold) {
            ++expansion;
        }
    }
    vec.reserve(vec.size() + expansion);

    for (auto it = vec.rbegin(); it != vec.rend(); ++it){
        if (*it >= threshold) {
            vec.push_back(*it);
        }
    }
}

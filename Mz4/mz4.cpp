#include <vector>
#include <algorithm>
#include <iterator>

template<class IdxIt, class ElemIt>
ElemIt myremove(IdxIt first_idx, IdxIt last_idx, ElemIt first, ElemIt last)
{
    std::vector<int> indices{};

    for (auto it = first_idx; it != last_idx; ++it) {
        indices.emplace_back(*it);
    }
    
    std::sort(indices.begin(), indices.end());
    indices.erase(std::unique(indices.begin(), indices.end()), indices.end());

    auto it = std::find_if(indices.begin(), indices.end(), [](int idx){
        return idx >= 0;
    });

    int len = std::distance(first, last);
    auto my_end = std::find_if(it, indices.end(), [len](int idx){
        return idx >= len;
    });

    ElemIt result = first;
    int curr_idx = 0;

    while (first != last && it != my_end) {
        if (curr_idx == *it) {
            ++it;
        } else {
            // The elememts of the container could be non-copyable
            // hence copy assignment could be unavailable
            // so we use std::move to force move assignment
            *result = std::move(*first);
            ++result;
        }
        ++first;
        ++curr_idx;
    }

    while (first != last) {
        *result = std::move(*first);
        ++first;
        ++result;
    }

    return result;
}
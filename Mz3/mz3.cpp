#include <algorithm>
#include <vector>
#include <iterator>

void process(const std::vector<int>& v1, std::vector<int>& v2){
    std::vector<int> indices{v1};

    std::sort(indices.begin(), indices.end());

    // remove duplicates
    auto last_it = std::unique(indices.begin(), indices.end());
    indices.erase(last_it, indices.end());
    
    // find the first non-negative index
    auto it = std::find_if(indices.begin(), indices.end(), [](int index) { 
        return index >= 0; 
    });

    // find the first invalid index
    int length = v2.size();
    auto myEnd = std::find_if(it, indices.end(), [length](int index) {
        return index >= length; 
    });

    if (it == myEnd) {
        // nothing to do
        return;
    }

    auto left = v2.begin() + *it;
    auto right = v2.begin() + *it + 1;
    int curr_index = *it + 1;
    // I'm gonna delete elements in range [left, right)

    ++it;
    while (it != myEnd && right != v2.end()) {

        if (curr_index != *it) {
            // shift the existing sequence
            std::swap(*left, *right); 
            ++left;

        } else {
            // the element is added to the sequence
            // since we don't swap

            // prepare next index we'll seek for
            ++it;
        }
        ++curr_index;
        ++right;
    }
    v2.erase(left, right);
}
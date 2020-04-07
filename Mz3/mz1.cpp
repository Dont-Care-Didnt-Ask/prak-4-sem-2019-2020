#include <vector>
#include <cstdint>
#include <iterator>

void process(const std::vector<uint64_t>& addendums, std::vector<uint64_t>& to_change, int step){
    auto dest_it = to_change.rbegin();
    auto src_it = addendums.begin();

    while (dest_it != to_change.rend() && src_it != addendums.end()){
        *dest_it += *src_it;
        ++dest_it;
        
        /*
        One does not simply write 'src_it += step'
        because this way you can jump out of the container
        and get big bad undefined behaviour.
        Or, even worse, you can get reject. 
        */
        auto diff = std::distance(src_it, addendums.end());
        src_it += (diff > step) ? step : diff;
    }
}

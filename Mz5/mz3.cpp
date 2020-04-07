#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <memory>
#include <map>
#include "up05-2.cpp"

// Using unique_ptr, we don't care about freeing memory
// unique_ptr will handle it himself
template <class T>
auto get_uniq(std::string str) -> std::unique_ptr<Figure>
{
    T *obj = T::make(str);
    return std::unique_ptr<Figure>(obj);
}

struct ClassFactory
{
private:
    // Connect figure type to their makers
    std::map<char, std::function<std::unique_ptr<Figure> (std::string)>> make_fig = {
        {'R', get_uniq<Rectangle>},
        {'S', get_uniq<Square>},
        {'C', get_uniq<Circle>}
    };
    // hide constructors and assignment operator in private section
    // one ClassFactory object, given by 'factory_instance', is enough
    ClassFactory(){}
    ClassFactory(const ClassFactory&){}
    ClassFactory& operator =(ClassFactory& ) = delete;

public:
    static ClassFactory factory_instance(){
        static ClassFactory instance{};
        return instance;
    }
    std::unique_ptr<Figure> operator ()(std::string str){
        if (str[0] == ' ') {
            // delete leading whitespaces, if needed
            auto it = str.begin();
            for(; it != str.end() && *it == ' '; ++it);
            str.erase(str.begin(), it);
        }
        char type = str[0];
        // delete type and leave parameters 
        str.erase(str.begin());
        
        return make_fig[type](str);
    }    
};

int Comp(const std::unique_ptr<Figure>& a, const std::unique_ptr<Figure>& b){
    return a->get_square() < b->get_square();
}

int main(){
    ClassFactory creator{ClassFactory::factory_instance()};
    std::string description;
    std::vector<std::unique_ptr<Figure>> everybody{};

    while(std::getline(std::cin, description)){
        everybody.emplace_back(creator(description));
    }
    std::stable_sort(everybody.begin(), everybody.end(), Comp);

    for(const auto& el : everybody){
        std::cout << el->to_string() << std::endl;
    }

    return 0;
}
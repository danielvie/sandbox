#include <algorithm>
#include <iostream>
#include <ranges>
#include <tuple>
#include <vector>

template <std::ranges::range R>
class IndexedRange {
public:
    IndexedRange(const R& r): the_range(r){}
    auto begin() const { return the_range.begin(); }
    auto end() const { return the_range.end(); }
private:
    const R& the_range;
};

class CI {
public:
    CI(int from=0, int step=1) : index{from}, by{step} {}
    template <typename T>
    auto operator() (T&& el){
        int i{index};
        index += by;
        return std::tuple{i, std::forward<T>(el)};
    }
private:
    int index;
    int by;
};

auto id(std::ranges::range auto&& v) { return std::forward<decltype(v)>(v); }

int main(){

    std::vector<int> vec { 3, 12, 4, 7 };
    IndexedRange ir{vec};

    namespace r = std::ranges;
    namespace v= r::views;
    r::sort(vec);
    for(auto el:vec){
        std::cout << el << '\n';
    }
    for(const auto& [index, value]: v::transform(vec,
            [](const auto& el){
                static int i;
                return std::tuple{i++, el};
            }
       )
    ){
        std::cout << index << ':' << value << '\n';
    }
    for(const auto& [index, value]: v::transform(vec, CI{0,2})){
        std::cout << index << ": " << value << '\n';
    }
    for(const auto& [index, value]: vec | v::transform(CI{0,2})){
        std::cout << index << ": " << value << '\n';
    }
    for(int index{0}; const auto& value: vec){
        std::cout << index++ << ": " << value << '\n';
    }
    std::initializer_list l{3, 4};
    if(std::ranges::range<decltype(l)>) { std::cout << "l is a range\n"; }
    if(std::ranges::viewable_range<decltype(l)>) { std::cout << "l is a viewable_range\n"; }
    begin(l);
#if 0
    for(const auto [index, value]: id(std::initializer_list{3.0, 4.5, 8.7}) | v::transform(CI{0,2})){
        std::cout << index << ": " << value << '\n';
    }
    for(const auto [index, value]: v::transform(std::initializer_list{3.0, 4.5, 8.7}, CI{0,2}) ){
        std::cout << index << ": " << value << '\n';
    }
#endif
    auto quad = [](const auto& el){return el*el;};
#if 0
    for(auto el: std::initializer_list{1, 2, 5, 8}
               | std::views::transform(quad)){
        std::cout << el << '\n';
    }
#endif
    for(std::initializer_list nums{1, 2, 5, 8};
           auto el: nums | std::views::transform(quad)){
        std::cout << el << '\n';
    }
    for(auto l = std::initializer_list{3.0, 4.5, 8.7}
       ; const auto [index, value]: l | v::transform(CI{0,2})){
        std::cout << index << ": " << value << '\n';
    }
    for(auto l = std::initializer_list{3.0, 4.5, 8.7}
       ; const auto [index, value]: v::transform(l, CI{0,2}) ){
        std::cout << index << ": " << value << '\n';
    }
    const auto il = std::initializer_list{3.0, 4.5, 8.7} ;
    auto t = il | v::transform(CI{0,2});

    for(const auto [index, value]: t){
        std::cout << index << ": " << value << '\n';
    }
    for(const auto [index, value]: il | v::transform(CI{0,2}) | v::take(2) ){
        std::cout << index << ": " << value << '\n';
    }
/*
    for(const auto& [index, value]: ir){
        std::cout << index << ':' << value << '\n';
    }
*/
    auto odds = std::views::iota(1,40)
              | std::views::filter([](const auto& el){return el % 2;});
    r::copy(odds, std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
    r::copy(odds|std::views::transform([](auto el){return el + 1;})
         , std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';
    r::copy(odds|std::views::transform([](auto el){return "[" + std::to_string(el) + "]";})
                |std::views::drop(4)
         , std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << '\n';
    static_assert(std::ranges::range<decltype(odds)>);
}
    

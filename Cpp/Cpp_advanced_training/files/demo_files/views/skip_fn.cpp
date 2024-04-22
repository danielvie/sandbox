#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

#include "tools.h"

template <std::ranges::range R>
void dump(R r){
    for(const auto& el: r){
        std::cout << el << ' ';;
    }
    std::cout << '\n';
}

int main(){
    namespace r = std::ranges;
    namespace views = r::views;

    std::vector v {3, 7, 9, 8 ,12, 20, 30, 50};

    auto nth_fn =
        [](int period=2, int start=0){
            return
                [period, start, location=0](auto) mutable {
                    location %= period;
                    return location++ == start;
                };
        };
    
    for(const auto& el: v|views::filter(nth_fn(3,1))){
        std::cout << el << ' ';;
    }
    std::cout << '\n';
    for(const auto & el: views::iota(0)|views::take(20)|views::filter(nth_fn(3,1))){
        std::cout << el << ' ';
    }
    std::cout << '\n';
    SHOW_IT_TAG<decltype(v.begin())>("vector");
    static_assert(std::contiguous_iterator<decltype(v.begin())>);
    using it_t = decltype((v|views::filter(nth_fn(3,1))).begin());
    SHOW_IT_TAG<it_t>("filter");
    static_assert(std::bidirectional_iterator<it_t>);
    std::cerr << std::flush;
    std::cout << std::flush;

    std::cout << std::string(30,'=') << '\n';
    auto second = views::filter(nth_fn(2, 1));
    dump(second(v));

    r::copy(second(v), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    r::copy(v|second, std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    auto third = views::filter(nth_fn(3, 2));
    dump(third(v));
}

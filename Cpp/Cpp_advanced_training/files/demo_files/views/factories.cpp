#include <iomanip>
#include <iostream>
#include <ranges>
#include <sstream>
#include <vector>

template <typename V>
void dump(V v){
    for(int n: v|std::views::take(2)){
        std::cout << n << ' ';
    }
    std::cout << '\n';
}
int main(){
    double d {4.5};

    auto d_v = std::ranges::single_view(d);
    auto d_v2 = std::views::single(d); // not d | single()

    for(auto& e: d_v){
        std::cout << e << ' ';
        e += 0.2; // copy of d stored!
    }
    std::cout << '\n';
    for(auto& e: d_v){
        std::cout << e << ' ';
    }
    std::cout << '\n';

    for(auto& e: d_v2){
        std::cout << e << ' ';
    }
    std::cout << '\n';

    auto e_v = std::ranges::empty_view<int>(); // needs type
    for(auto& e: e_v){
        std::cout << e << ' ';
    }
    std::cout << '\n';

    auto i_v = std::ranges::iota_view(3, 7);
    for(const auto& e: i_v){ // iota delivers const
        std::cout << e << ' ';
    }
    std::cout << '\n';

    auto i_v2 = std::ranges::iota_view(90);
    for(const auto& e: i_v2){
        std::cout << e << ' ';
        if(e > 500) break;
    }
    std::cout << '\n';

    std::istringstream is{"Three loud bangs from .\\.."};
    // no std::views::istream (compiler issue?)
    auto s_v = std::ranges::istream_view<std::string>(is);
    for(const auto& e: s_v){
        std::cout << std::quoted(e,'/') << ' ';
    }
    std::cout << '\n';

    // This is about where to use all()
    //std::vector<int> vec {1,2,5,6};
    int vec[] {1,2,5,6};
    for(int n: vec|std::views::take(2)){
        std::cout << n << ' ';
    }
    std::cout << '\n';
    dump(std::views::all(vec));
}

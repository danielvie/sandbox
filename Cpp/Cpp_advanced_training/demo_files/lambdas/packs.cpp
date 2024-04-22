#include <iostream>

// In a capture forwarding is silly, cause you can only forward once!
auto f(auto ... params){
    auto l1 = [params...]{ (std::cout << ... << params); };
    auto l2 = [...pack=params]{ (std::cout << ... << pack); };
    auto l3 = [&...pack=params]{ (std::cout << ... << pack); };
    l1();
    std::cout << '\n';
    l2();
    std::cout << '\n';
    l3();
    std::cout << '\n';
}

int main(){
    using namespace std::literals;
    f(3, 4.5, "Hello"s);
}

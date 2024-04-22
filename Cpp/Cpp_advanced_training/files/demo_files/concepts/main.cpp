#include <iostream>
#include <string>
#include <concepts>

#include "tools.h"

void f(auto n) {
    std::cout << "other" << '\n';
    TRACE();
}

void f(std::integral auto n) {
    std::cout << "integral" << '\n';
    TRACE();
}

/*
void f(std::unsigned_integral auto n) {
    std::cout << "unsigned integral" << '\n';
    TRACE();
}
*/

void f(std::signed_integral auto n) {
    std::cout << "signed integral" << '\n';
    TRACE();
}

template <typename T>
void g(T n) {
    std::cout << "other" << '\n';
    TRACE();
}

template <std::integral Number>
void g(Number n) {
    std::cout << "integral" << '\n';
    TRACE();
}

/*
template <std::unsigned_integral Number>
void g(Number n) {
    std::cout << "unsigned integral" << '\n';
    TRACE();
}
*/

template <std::signed_integral Number>
void g(Number n) {
    std::cout << "signed integral" << '\n';
    TRACE();
}

class X {};

int main() {
    f(3);          // signed integral
    f(30000000LL); // signed integral
    f(3Lu);        // integral
    f(X{});        // other
    if constexpr (std::signed_integral<decltype(3)>){
        std::cout << "signed_integral used as a predicate" << '\n';
    }
    g(3);          // signed integral
    g(30000000LL); // signed integral
    g(3Lu);        // integral
    g(X{});        // other

    auto l = [](std::integral auto n) { std::cout << "integral" << '\n'; };
    l(3);
    //l(3.4); // doesn't compile
}

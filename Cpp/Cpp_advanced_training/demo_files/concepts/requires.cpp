#include <concepts>
#include <iostream>
#include <iterator>
#include <list>

#include "tools.h"

auto func2(std::bidirectional_iterator auto iter) {
    TRACE();
}

template <typename T>
auto func(T iter)
        requires std::bidirectional_iterator<T> {
    TRACE();
}

template <typename T>
auto func_int(T iter)
        requires std::bidirectional_iterator<T>
        && std::integral<std::iter_value_t<T>> {
    TRACE();
}

template <typename T>
concept integral_iter =
        std::bidirectional_iterator<T>
        && std::integral<std::iter_value_t<T>>;

auto func_concept(integral_iter auto iter){
    std::cerr << "integral_iter\n";
    TRACE();
}

auto func_concept(std::bidirectional_iterator auto iter){
    std::cerr << "bidirectional_iter\n";
    TRACE();
}

template <typename T>
concept barking =
    requires(T t){
        t.bark();
    };

void bark(barking auto dog){
    dog.bark();
}

template <typename T, typename ... More>
void bark2(T dog, More ... m) requires
    requires(){
        dog.bark(m...);
    }
{
    dog.bark(m...);
}

struct Dog {
    void bark(const int& x=0){
        std::cout << "waf\n";
    }
};

template <typename T>
concept has_iter =
    requires {
        typename T::iterator;
        typename T::const_iterator;
    };

template <typename T>
concept int_add =
    requires (T n) {
        { n + 1 } noexcept -> std::same_as<int>;
    };

template <typename T>
concept copy_iter = std::copy_constructible<T> &&
    requires (T n) {
        requires std::copy_constructible<typename T::iterator>;
    };

#if 0
// None-namespace scope
struct Nested {
    template <typename T>
    concept special = std::move_constructible<T>;
    void f(special auto s){}
};
#endif

int main(){
    int *ip;
    func(ip);
    func2(ip);
    auto func_l = []<typename T>(T iter)
        requires std::bidirectional_iterator<T> {
            TRACE();
        }; 
    func_l(ip);

    std::list li {3, 4};
    func_int(ip);
    func_int(li.begin());
    func_l(li.begin());

    func_concept(ip);
    func_concept(li.begin());
    std::list ld {3.4, 4.5};
    func_concept(ld.begin());

    //bark(li);
    bark(Dog());
    bark2(Dog());
    bark2(Dog(), 4);
    bark2(Dog(), 4.5); // double converts to int
    //bark2(Dog(), "...");
    static_assert(!has_iter<int>);
    static_assert(has_iter<std::list<int>>);
    static_assert(int_add<int>);
    static_assert(!int_add<std::list<int>>);
    static_assert(!copy_iter<int>);
    static_assert(copy_iter<std::list<int>>);
}

#include <iostream>
#include <version>

#if __cplusplus <= 201703
#define CPP20 0
#else
#define CPP20 1
#endif

#if CPP20
template <typename T>
using X = T::X;
#else
template <typename T>
using X = typename T::X;
#endif


template <typename T>
struct Z : T::X {
#if CPP20
    T::X * m;
    auto f(T::X p=typename T::X{}){
        typename T::X * t;
    }
#else
    typename T::X * m;
    auto f(typename T::X p=typename T::X{}){
        typename T::X * t;
    }
#endif
};

int main(){
    std::cout << __cplusplus << '\n';
    std::cout << CPP20 << '\n';
}

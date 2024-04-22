#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <version>

constexpr int fac(int n){ return (std::is_constant_evaluated()? 1000 : 0) + (n < 2 ? n : n*fac(n-1)) ; };
consteval int cfac(int n){ return (n < 2 ? n : n*cfac(n-1)) ; };
constexpr int puke(int n) { if (n > 10) throw 7; return n;}

int main(int argc, char *argv[]){
    constinit static int start{17+5};
    constexpr static int other{14};
    //++other; // read-only
    ++start;
    const int x{6};
    const int i{x-3};
    constexpr auto r {fac(i)};
    std::cout << r << '\n';
    std::cout << fac(argc) << '\n';
    //std::cout << cfac(argc) << '\n';// argc must be const
#if 0
    // Should work, but gcc's libstd is not yet up to it.
    constexpr std::string s("Hallo");
    static_assert(s[3] == 'l');
    static_assert(s.zie() == 5);
    constexpr std::vector v{3, 4, 5};
    static_assert(v[1] == 4);
    static_assert(v.size() = 3);
    // This probably throw a compile time exception.
    const int lots{10'000};
    constexpr std::vector v2(lots, 12);
    static_assert(v2.size() == lots);
#endif
    constexpr int n = puke(8);
    constexpr std::pair p{3, 6.7};
    auto&[key, value] = p;
    static_assert(std::get<0>(p) == 3);
   // static_assert(key == 3);
}

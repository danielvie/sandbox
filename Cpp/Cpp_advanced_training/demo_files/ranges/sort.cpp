#include <algorithm>
#include <chrono>
#include <iostream>
#include <ranges>
#include <tuple>
#include <vector>

template <typename Fn, typename ... Types>
    requires std::invocable<Fn, Types...>
auto time_this(Fn f,Types&& ... parms){
    namespace c = std::chrono;
    auto now = []{ return c::high_resolution_clock::now(); };
    auto start = now();
    invoke(f, std::forward<Types>(parms)...);
    return c::duration_cast<c::microseconds>(now() - start).count();
}

auto display_pack(auto&& ...){
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

int main(){
    using namespace std::literals;
    namespace r = std::ranges;
    /*constexpr*/
    std::vector src { "hello"s, "goodbye"s, "wiedersehen"s, "tot ziens"s, "bye bye"s };

    auto words{src};
    for(const auto& w: words){ std::cout << w << '\n'; }
    r::sort(words);
    for(const auto& w: words){ std::cout << w << '\n'; }
    words = src;
    r::sort(words, {}, [](auto s){ r::reverse(s); return s; });
    for(const auto& w: words){ std::cout << w << '\n'; }
    words = src;
    // Waarom werkt {} wel als parameter van sort, maar niet via een pack?
    // Duidelijk: in sort is het de default constructor van r:less
    // in het pack is het anoniem.
    auto took = time_this(r::sort, words, r::less{}, [](auto s){ r::reverse(s); return s; });
    for(const auto& w: words){ std::cout << w << '\n'; }
    std::cout << "Took: " << took << " micros\n";
    words = src;
    auto took2 = time_this(r::sort, words, [](auto s, auto t){ r::reverse(s); r::reverse(t); return s < t; });
    for(const auto& w: words){ std::cout << w << '\n'; }
    std::cout << "Took: " << took2 << " micros\n";
    // Wat de {} in een pack dan betekent is mij vooralsnog een raadsel.
    // Het pack is leeg als ik {} gebruik (Types = {}) en g++ klaagt over te
    // veel parameters (als ik r::less weglaat).
    display_pack(3, r::less{}, []{});

    std::vector<float> fv {3.4, 5.6};
    r::sort(fv);
}
    

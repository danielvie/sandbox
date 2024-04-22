#include <memory>
#include <type_traits>
#include "tools.h"

template <typename T>
concept bounded_array = std::is_bounded_array_v<T>;

template <typename T>
concept unbounded_array = std::is_unbounded_array_v<T>;

template <typename T, size_t N>
concept sized_array = bounded_array<T>
    && std::is_convertible_v<std::extent<T>,
                             std::integral_constant<std::size_t, N>>;

template <typename T>
void f() { std::cerr << "any "; TRACE(); }
template <bounded_array T> requires std::is_convertible_v<std::extent<T>,
                                 std::integral_constant<std::size_t, 99>>
void f() { std::cerr << "[99] "; TRACE(); }
template <sized_array<77> T> 
void f() { std::cerr << "[77] "; TRACE(); }
template <bounded_array T>
void f() { std::cerr << "[#] "; TRACE(); }
template <unbounded_array T>
void f() { std::cerr << "[]  "; TRACE(); }

template <typename T, typename ... P>
auto mu(P&& ... params) {
    return std::unique_ptr<T>(new T (std::forward<P>(params)...));
}

template <unbounded_array T, std::convertible_to<size_t> N>
auto mu(N n) {
    using Elem = std::remove_extent_t<T>;
    return std::unique_ptr<Elem[]>(new Elem [n]);
}

template <bounded_array T, typename ... P>
void mu(P&& ...) = delete;

int main(){
    static_assert(std::is_bounded_array_v<int[4]>);
    //static_assert(!std::is_bounded_array_v<int[0]>); // !!!
    static_assert(!std::is_bounded_array_v<int[]>);
    static_assert(!std::is_unbounded_array_v<int[4]>);
    static_assert(std::is_unbounded_array_v<int[]>);
    //static_assert(!std::is_unbounded_array_v<int[0]>); // !!!
    static_assert(std::extent_v<int[]> == 0);
    //static_assert(std::extent_v<int[0]> == 0);
    static_assert(std::extent_v<int[4]> == 4);
    f<int>();
    f<int[]>();
    f<int[99]>();
    f<int[77]>();
    f<int[5]>();

    auto p = mu<int>(3);
    auto q = mu<int[]>(7);
    static_assert(std::is_same_v<decltype(p), std::unique_ptr<int>>);
    static_assert(std::is_same_v<decltype(q), std::unique_ptr<int[]>>);
   // auto x = mu<int[4]>(77, "aap", 4.5);
   // auto x2 = mu<int[]>("hello");
}

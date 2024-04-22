#include <concepts>
#include <string>

#include <compare>

#include "tools.h"
template <typename ...Types>
//requires std::three_way_comparable<Types>...
using common_cat = std::common_comparison_category<decltype(std::declval<Types>()<=>std::declval<Types>())...>;

template <typename ...Types>
using common_cat_t = common_cat<Types...>::type;

template <typename N>
concept Number = std::integral<N> || std::floating_point<N>;

template <Number N>
class Point {
public:
    constexpr Point(N x, N y): x(x), y(y) {}
    constexpr auto get_x() const { return x; }
    constexpr auto operator <=> (const Point&) const = default;
    //constexpr std::weak_ordering operator <=> (const Point&) const = default;
private:
    N x;
    N y;
};

template <Number N>
class Vec {
public:
    constexpr Vec(N x, N y): x(x), y(y) {}
    constexpr auto get_x() const { return x; }
    constexpr std::weak_ordering operator <=> (const Vec& p) const {
        return (x*x + y*y) <=> (p.x*p.x + p.y*p.y);
    }
    constexpr bool operator == (const Vec& p) const = default;
#if 0
    constexpr auto operator == (const Vec& p) const {
        return (*this <=> p ) == 0;
    }
#endif
private:
    N x;
    N y;
};

int main(){
    constexpr Point p1 {3,4};
    constexpr Point p2 {5,7};

    constexpr Vec pr1 {3,4};
    constexpr Vec pr2 {4,3};

    static_assert(p1 < p2);
#if 0
    static_assert(!(pr1 < pr2));
    static_assert(!(pr2 < pr1));
#endif
    //static_assert(pr1 == pr2);
    static_assert(pr1.get_x() != pr2.get_x());

    WHAT<decltype(p1 <=> p2)>("Point");

    WHAT<common_cat_t<Point<int>>>("Point");
    WHAT<common_cat_t<Point<double>>>("Point<double>");
    SHOW_ORDERING<decltype(std::declval<Point<int>>() == std::declval<Point<int>>())>("Point ==");
    WHAT<decltype(std::declval<Point<int>>() == std::declval<Point<int>>())>("Point ==");
    WHAT<common_cat_t<double>>("double");
    static_assert(std::strict_weak_order<std::less<>, double, double>);
    WHAT<common_cat_t<Vec<int>>>("Vec");
    WHAT<common_cat_t<decltype(std::declval<Vec<int>>() == std::declval<Vec<int>>())>>("Vec ==");
    SHOW_ORDERING<decltype(std::declval<Vec<int>>() == std::declval<Vec<int>>())>("Vec ==");
    WHAT<decltype(std::declval<Vec<int>>() == std::declval<Vec<int>>())>("Vec ==");
    WHAT<common_cat_t<int, std::string>>("int, string");
    WHAT<common_cat_t<int, std::string, Point<int>>>("int, string, Point");
    WHAT<common_cat_t<int, std::string, Vec<int>>>("int, string, Vec");
}

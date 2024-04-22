#include <iostream>
#include <ranges>
#include <vector>

#include "tools.h"

template <typename T>
class nth : std::ranges::view_interface<nth<T>> {
public:
    using const_iterator = decltype 
    nth() = default;
    nth(const T& r, int p=2, int s=0) : m_begin{r.begin()}, m_end{r.end()}, period{p}, start{s}, location{0} {}
    class iterator;
    const_iterator begin() const { return m_begin; }
    const_sentinel end() const { return m_end; }
private:
    T::const_iterator m_begin;
    T::const_sentinel m_end;
    int period, start, location;
};

template <typename T>
class nth<T>::iterator {
public:
    iterator(nth<T> * n): view{n}{}
    iterator& operator ++ () {
        view->location %= view->period;
        ++(view->m_begin);
        return view->location++ == view->start;
    };
private:
    nth<T> view;
};

int main(){
    namespace r = std::ranges;
    namespace views = r::views;

    std::vector v {3, 7, 9, 8 ,12, 20, 30, 50};

    SHOW_IT_TAG<decltype(v.begin())>("vector");
    static_assert(std::contiguous_iterator<decltype(v.begin())>);
    using it_t = nth<std::vector<int>>::iterator;
    SHOW_IT_TAG<it_t>("filter");
    //static_assert(std::bidirectional_iterator<it_t>);
}

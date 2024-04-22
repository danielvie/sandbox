#include <iostream>
#include <list>
#include <ranges>
#include <vector>

namespace at::ranges {
    template <std::ranges::forward_range R, ssize_t N=2>
        //requires std::ranges::viewable_range<R>
    class Rotor_view:
        public std::ranges::view_interface<Rotor_view<R, N>> {
    public:
        using Base = std::ranges::view_interface<Rotor_view<R, N>>;
        class iterator;
        class sentinel;
        Rotor_view(R& r): m_range(r) {}
        auto begin() { return iterator(m_range.begin()); }
        auto end() { return sentinel(m_range.end()); }
        // auto size() { return Base::size()-(N-1); } // If available
    private:
        R m_range;
    };

    template <typename R, ssize_t N>
    class Rotor_view<R, N>::iterator {
    public:
        using WrappedIterator = std::ranges::iterator_t<R>;
        iterator(WrappedIterator it):m_it{it}{}
        bool operator == (iterator it){ return it.m_it == m_it; }
        bool operator == (sentinel s){ return s.at_sentinel(m_it); }
        auto operator ++ () {
            ++m_it;
            return *this;
        }
        auto operator * () {
            auto last = m_it;
            std::advance(last, N);
            return std::ranges::subrange(m_it, last);
        }
    private:
        WrappedIterator m_it;
    };
    template <typename R, ssize_t N>
    class Rotor_view<R, N>::sentinel {
    public:
        using WrappedSentinel = std::ranges::sentinel_t<R>;
        sentinel(WrappedSentinel s):m_s{s}{}
        bool at_sentinel(auto wrapped_it){
            std::advance(wrapped_it, (N-1));
            return m_s == wrapped_it;
        }
    private:
        WrappedSentinel m_s;
    };
}
namespace at::ranges::views {
    template <ssize_t N=2>
    //class Rotor: public std::ranges::views::__adaptor::_RangeAdaptor<Rotor<N>> {
    class Rotor {
    };
    template <std::ranges::range R, ssize_t N=2>
    auto operator | (R&& r, Rotor<N>){
        return  at::ranges::Rotor_view<R, N>(std::forward<R>(r));
    }
}
namespace at {
    namespace views = ranges::views;
}
template <typename T>
concept has_begin = requires(T& t){
    std::ranges::begin(t);
};
template <typename T>
concept has_end = requires(T& t){
    std::ranges::end(t);
};
template <typename T>
concept has_begin_end = requires(T& t){
    std::ranges::begin(t);
    std::ranges::end(t);
};

int main(){
    std::list<std::string> bones {
             "toe", "foot", "heel", "ankle",
             "leg", "knee", "thigh", "hip",
             "back", "shoulder", "neck", "head"};

    static_assert(std::ranges::range<std::vector<std::string>>);
#if 0
    static_assert(std::ranges::range<at::ranges::Rotor_view<std::vector<std::string>>>);
    static_assert(has_begin<at::ranges::Rotor_view<std::vector<std::string>>>);
    static_assert(has_end<at::ranges::Rotor_view<std::vector<std::string>>>);
    static_assert(has_begin_end<at::ranges::Rotor_view<std::vector<std::string>>>);
#endif
    auto pairs = at::ranges::Rotor_view(bones);
    auto pairs2 = bones | at::views::Rotor<2>();

    static_assert(std::ranges::viewable_range<decltype(std::ranges::views::all(bones))>);

    for(const auto& p: pairs2){
        for(const auto& bone: p){
            std::cout << bone << ' ';
        }
        std::cout << '\n';
    }
    for(const auto& p: pairs){
        auto q = p.begin();
        auto r = q;
        ++r;
        std::cout << "your " << *q << " bone connected to your " << *r << " bone\n";
    }
}



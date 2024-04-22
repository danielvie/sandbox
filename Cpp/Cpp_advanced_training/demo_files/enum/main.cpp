#include <version>
#include <iostream>
#include <type_traits>
#if __cpp_using_enum >= 201907L
#  define YEP 1
#else
#  define YEP 0
#endif
class V {
public:
    enum class Scoped { A, B, C };
    constexpr Scoped f() const { return Scoped::B; };
};

class W {
public:
    enum class Scoped { A, B, C };
#if YEP
    using enum Scoped;
    constexpr Scoped f() const { return B; };
#else
    constexpr Scoped f() const { return Scoped::B; };
#endif
};
// could use concept here, but is_scoped_enum will be in c++23
template <typename Enum>
auto to_underlying(Enum e){
    return static_cast<std::underlying_type_t<Enum>>(e);
}

int main(){
    V v;
    W w;

    switch(v.f()){
    case V::Scoped::A: ;;
    case V::Scoped::B: ;;
    case V::Scoped::C: ;;
    }

#if YEP
    switch(v.f()){
    // Doesn't work with gcc 10.1, need 11.1 for that.
    using enum V::Scoped;
    case A: ;;
    case B: ;;
    case C: ;;
    }

    switch(v.f()){
    using V::Scoped::A;
    case A: ;;
    case V::Scoped::B: ;;
    case V::Scoped::C: ;;
    }

    switch(w.f()){
    case W::A: ;;
    case W::B: ;;
    case W::C: ;;
    }
#else
    //[[deprecated("Using enum is NOT supported!")]] int x;
    //x++;
#warning "Using enum is NOT supported!"
    //std::cerr << "Using enum is NOT supported!\n";
#endif

    static_assert(std::is_same_v<std::underlying_type_t<V::Scoped>, int>);
    auto val = //
        static_cast<//
	    std::underlying_type_t<V::Scoped>//
        >(V::Scoped::A);
    static_assert(std::is_same_v<decltype(val), int>);
    auto val2 = to_underlying(V::Scoped::A); // 23 has this in std::
    static_assert(std::is_same_v<decltype(val2), int>);
}

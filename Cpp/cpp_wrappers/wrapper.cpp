#include <iostream>
#include <type_traits>

#include "rectangle.h"

using namespace std;

template <typename T>
class wrap_traits
{
public:
    static void prefix(const T &) { cout << "\nprefix\n"; }
    static void sufix(const T &) { cout << "sufix\n\n"; }
};

template <typename T, typename Traits = wrap_traits<T>>
class Wrap
{
private:
    T *p;
    class CallProxy
    {
    public:
        CallProxy(T *p_) : p(p_){};
        T *operator->() { return p; }
        ~CallProxy() { Traits::sufix(*p); };

    private:
        T *p;
    };

public:
    Wrap(T *p_) : p(p_) {}
    CallProxy operator->()
    {
        Traits::prefix(*p);
        return CallProxy(p);
    }
};

// struct S {
//     void operator()() const {}
// };

int main()
{
    Wrap<Rectangle> a = new Rectangle(10, 11, 18, 19);
    Wrap<Rectangle> b = new Rectangle(12, 1, 19, 10);

    cout << "Surface a: " << a->surf() << "\n";
    cout << "Surface b: " << b->surf() << "\n";

    return 0;
}

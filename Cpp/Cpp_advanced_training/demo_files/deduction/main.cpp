#include <initializer_list>
#include "tools.h"

template <typename T>
class Z {
public:
    Z(std::initializer_list<T>){TRACE();}
    Z(const Z&){TRACE();}
    Z(T, T){TRACE();}
};

int main(){
    Z z1(2, 3);
    Z z2{2, 3};
    Z z3(z1);
    Z z4{z1};
    Z z5{z1, z1};
}

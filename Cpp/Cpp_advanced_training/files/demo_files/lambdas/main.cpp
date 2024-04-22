#include <iostream>

struct Z {
    void f(){ auto g = [=,this](){ m; }; }
    int m;
};
auto f(auto n) { return n*n; }
int main(){
    auto l = []<typename T>(auto a, T t1, T t2, auto b) {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    };
    l(5.6, 4, 3, "Hello");
    std:: cout << f(3) << ' ' << f(3.4) << '\n';
}
    

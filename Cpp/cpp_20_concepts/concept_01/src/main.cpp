#include <iostream>
#include <concepts>
#include <format>

template <typename T>
concept Integral = std::is_integral_v<T>;

template <Integral T>
T add(T a, T b) {
    return a + b;
}

int main() {
    int x = 5;
    int y = 10;
    // Works fine
    auto r = add(x, y); 
    std::cout << "\n";
    std::cout << std::format("{} + {} = {}", x, y, r) << "\n";
    
    // Will give a compile-time error
    // add(5.0, 10.0);
}

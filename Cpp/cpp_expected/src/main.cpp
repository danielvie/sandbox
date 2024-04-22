#include <iostream>
#include <expected>
#include <optional>

struct Divider {
    double v;
    Divider(double v) : v(v) {}
};

struct Adder {
    double v;
    Adder(double v) : v(v) {}
};

struct Multiplier {
    double v;
    Multiplier(double v) : v(v) {}
};

std::expected<double, std::string> operator|(std::expected<double, std::string> n, Divider(v)) {
    if (!n) { return n; }
    
    if (v.v == 0) {
        return std::unexpected("Division by zero");
    }

    return n.value() / v.v;
};

std::expected<double, std::string> operator|(std::expected<double, std::string> n, Adder(v)) {
    if (!n) { return n; }

    return n.value() + v.v;
};

std::expected<double, std::string> operator|(std::expected<double, std::string> n, Multiplier(v)) {
    if (!n) { return n; }
    
    return n.value() * v.v;
}

std::optional<std::string> convertToText(int num) {
    return std::to_string(num);
}

int main() {

    auto res = 100
                | Divider(2.0)
                | Multiplier(2.0)
                | Adder(20.0)
                | Adder(20.0)
                | Multiplier(3.0)
                | Multiplier(3.0)
                | Adder(20.0)
                | Divider(1.0);

    if (res) {
        std::cout << "my value is: " << res.value() << std::endl;
    } else {
        std::cout << res.error() << std::endl;
    }

    return 0;
}

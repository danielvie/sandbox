#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main(int argc, char const *argv[]) {
    std::vector<double> input(10);
    
    double start = 0;
    
    for ( auto &element : input ) {
        element = start += 1.0;
    }
    
    std::vector<double> output(10);
    
    std::transform(std::execution::par, input.begin(), input.end(), output.begin(), [](double x) {
        return x * x;
    });
    
    for ( auto &element : output ) {
        std::cout << element << std::endl;
    }
    
    return 0;
}

#include <iostream>
#include "sum.hh"

#include <Eigen/Dense>
#include <string>

int main(int argc, char const *argv[])
{
    std::cout << "hello\n";
    std::cout << "sum equal: " << sum(10.0f, 10.0f) << std::endl;
    
    Eigen::Vector2d v2 {1.0, 2.0};
    
    std::cout << v2.norm() << "\n";

    std::string bla;

    return 0;
}


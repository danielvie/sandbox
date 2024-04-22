#include <iostream>
#include "add.h"
#include "sub.h"
#include "mul.h"
#include <random>

int main()
{
    srand(time(0));
    
    int a = std::rand() % 10000;
    int b = std::rand() % 10000;

    std::cout << "==================================\n";
    printf("code is here: add(%d, %d): %d\n", a, b, add(a,b));
    printf("code is here: sub(%d, %d): %d\n", a, b, sub(a,b));
    printf("code is here: mul(%d, %d): %d\n", a, b, mul(a,b));
    // std::cout << "a: " << a << std::endl;
    // std::cout << "b: " << b << std::endl;
    // std::cout << "add(3,5): " << add(3,5) << std::endl;
    std::cout << "mado uhhahahaha\n";
    std::cout << "==================================\n";
    return 0;
}
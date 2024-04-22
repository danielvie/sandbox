#include <chrono>
#include <iostream>
#include <thread>
#include <type_traits>
#include <version>

#include "tools.h"

int main(){
    std::ios::sync_with_stdio(false);
    auto f = [](int ms){
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        std::cout << "thread ";
        std::cout << ms;
        std::cout << '\n';
        std::cout << std::flush;
    };
    auto t1 = std::jthread(f, 200);
    auto t2 = std::jthread(f, 200);
    auto t3 = std::jthread(f, 200);
    std::cout << "main" << '\n';
    std::cout << std::flush;
}

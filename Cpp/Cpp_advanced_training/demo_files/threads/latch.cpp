#include <chrono>
#include <iostream>
#include <latch>
#include <thread>
#include <type_traits>

#include "tools.h"

int main(){
    std::counting_semaphore<4> quattro{4};
    std::binary_semaphore single{1};

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

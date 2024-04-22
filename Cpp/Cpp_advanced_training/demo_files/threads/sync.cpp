#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>
#include <type_traits>
#include <version>

#include "tools.h"

int main(){
    std::ios::sync_with_stdio(false);
    using namespace std::literals;
    auto f = [](int ms){
        std::osyncstream s_cout{std::cout};
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        s_cout << "thread ";
        s_cout << ms;
        s_cout << '\n';
    };
    auto t1 = std::jthread(f, 200);
    auto t2 = std::jthread(f, 200);
    auto t3 = std::jthread(f, 200);
    std::osyncstream sync_cout{std::cout};
    sync_cout << "main" << '\n';
}

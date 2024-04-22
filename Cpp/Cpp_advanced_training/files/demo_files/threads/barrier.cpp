#include <chrono>
#include <iostream>
#include <barrier>
#include <thread>
#include <type_traits>

#include "tools.h"

int main(){
    auto complete = []() noexcept {
        static int n{1};
        std::cout << "going " << n << '\n';
        ++n;
    };
    std::barrier hurdle{2, complete};

    auto f = [&hurdle](int ms){
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        auto arrival_token = hurdle.arrive();  // hurdle.wait(hurdle.arrive())
        hurdle.wait(std::move(arrival_token)); // also hurdle.arrive_and_wait()
        std::cout << "thread " << ms << '\n';
    };
    auto t1 = std::jthread(f, 200);
    auto t2 = std::jthread(f, 199);
    auto t3 = std::jthread(f, 198);
    auto t4 = std::jthread(f, 197);
    std::cout << "main" << '\n';
    std::cout << std::flush;
}

#include <chrono>
#include <iostream>
#include <semaphore>
#include <thread>
#include <type_traits>

#include "sync_out.h"

int main(){
    using namespace std::literals;
    std::ios::sync_with_stdio(false);

    std::counting_semaphore<1> give{0};
    std::binary_semaphore got{0};

    int resource{0};

    auto produce = [&give, &got, &resource](std::stop_token token){
        while(!token.stop_requested()){
            give.acquire();
            resource++;
            sync_out("producing ", resource);
            got.release();
        }
    };
    auto p = std::jthread(produce);
    auto consume = [&give, &got, &resource](std::stop_token token){
        give.release();
        while(!token.stop_requested()){
            got.acquire();
            sync_out("consuming ", resource);
            std::this_thread::sleep_for(200ms);
            give.release();
        }
    };
    auto c = std::jthread(consume);

    sync_out("main");
    std::this_thread::sleep_for(400ms);
    p.request_stop();
    c.request_stop();
    std::this_thread::sleep_for(20ms);

    static_assert(std::is_same_v<std::counting_semaphore<1>,
                                 std::binary_semaphore>);
}

#include <chrono>
#include <iostream>
#include <thread>
#include <type_traits>
#include <version>

#include "sync_out.h"
#include "tools.h"

int main(){
    using namespace std::chrono_literals;
    std::ios::sync_with_stdio(false);
    auto f = [](std::stop_token token, int ms){
        auto some_time = std::chrono::milliseconds(ms);
        while(!token.stop_requested()){
            std::this_thread::sleep_for(some_time);
            sync_out("thread", ms);
        }
    };
    auto t1 = std::jthread(f, 200);
    auto t2 = std::jthread(f, 199);
    auto t3 = std::jthread(f, 1980);
    std::stop_callback cb(t3.get_stop_token(),
              [](){sync_out("ouch"); });
    std::this_thread::sleep_for(600ms);
    sync_out("stopping 1980");
    t3.request_stop();
    std::this_thread::sleep_for(300ms);
  //  return 0;
    sync_out("stopping 1980 (again)");
    t3.request_stop(); // no-op, already done
    sync_out("joining 1980");
    t3.join();
    sync_out("stopping 199");
    t2.request_stop();
    sync_out("joining 199");
    t2.join();
    sync_out("stopping 200");
    t1.request_stop();
    sync_out("joining 200");
    t1.join();
}

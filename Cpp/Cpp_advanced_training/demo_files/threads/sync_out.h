#pragma once

#include <iostream>
#include <syncstream>

template <typename ... T>
void sync_out(T&& ... args){
    std::osyncstream synced{std::cout};
    (synced << ... << std::forward<T>(args));
    synced << std::endl;
}

cmake_minimum_required(VERSION 3.20.0)
project(Hello)
include_directories(lib)

file(GLOB LIB "lib/*.cpp")
add_executable(Hello src/hello.cpp)
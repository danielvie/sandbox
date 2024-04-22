cmake_minimum_required(VERSION 3.20.0)
project(Main)

set(CMAKE_CXX_STANDARD 17)

include_directories(fun)
include_directories(src)

file(GLOB mySources CONFIGURE_DEPENDS "src/*.cpp" "fun/*.cpp")
add_executable(Main src/main.cpp)
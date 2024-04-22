cmake_minimum_required(VERSION 3.20.0)
project(Main)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/qpOASES/include)
include_directories(src)


file(GLOB mySources CONFIGURE_DEPENDS "src/*.cpp" "src/qpOASES/src/*.cpp")
add_executable(Main ${mySources})

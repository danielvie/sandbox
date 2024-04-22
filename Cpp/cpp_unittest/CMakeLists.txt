cmake_minimum_required(VERSION 3.20)
project(unittest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

include_directories(src)

enable_testing()

# Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB my_sources CONFIGURE_DEPENDS "src/*.cpp")
add_executable(unittest ${my_sources})
target_link_libraries(unittest ${GTEST_BOTH_LIBRARIES})
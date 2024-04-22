cmake_minimum_required(VERSION 3.20)
project(algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(TBB REQUIRED)
include_directories(${TBB_INCLUDE_DIRS})

add_executable(transform src/transform.cc)
target_link_libraries(transform ${TBB_IMPORTED_TARGETS})
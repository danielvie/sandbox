cmake_minimum_required(VERSION 3.20)
project(tutorial)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Eigen3 REQUIRED)
add_library(sum lib/sum.cc)
target_include_directories(sum PUBLIC 
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>
)

add_executable(main src/main.cc)
target_link_libraries(main sum Eigen3::Eigen)

# installation and export
install(
    DIRECTORY include/
    DESTINATION include
)

install(TARGETS sum
    EXPORT sum-targets
    ARCHIVE DESTINATION lib
)

install(EXPORT sum-targets
    NAMESPACE something::
    DESTINATION lib/cmake/sum
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/sum-config.cmake.in sum-config.cmake 
                COPYONLY)

install(FILES
${CMAKE_BINARY_DIR}/sum-config.cmake
DESTINATION lib/cmake/sum
)

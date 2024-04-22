cmake_minimum_required(VERSION 3.12)
project(extension)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(python_path "/Users/danielvieira/.pyenv/versions/3.11.2/")
set(numpy_path "${python_path}/lib/python3.11/site-packages/numpy/core/include/")

message(STATUS "Python path: ${python_path}")
message(STATUS "Numpy path: ${numpy_path}")

include_directories(${python_path}/include/python3.11)
include_directories(${numpy_path})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -D_hypot=hypot -DNPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -D_hypot=hypot -DNPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION")

link_directories(${python_path}/lib)
add_library(extension SHARED ${CMAKE_SOURCE_DIR}/extension.cpp)
target_link_libraries(extension python3.11)

set_target_properties(extension PROPERTIES PREFIX "")
if(WIN32)
    set_target_properties(extension PROPERTIES SUFFIX ".pyd")
else()
    set_target_properties(extension PROPERTIES SUFFIX ".so")
endif()

# copy extension to root
add_custom_command(TARGET extension POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/py
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:extension> ${CMAKE_SOURCE_DIR}
    COMMENT "Copying extension to `py` directory"
)
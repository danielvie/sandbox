all: i

i: init

c: clean

default:
	cmake -B ./build
	cmake --build ./build
	./build/hello

init: create_cmakelists

dol = $$

create_cmakelists:
	printf "cmake_minimum_required(VERSION 3.20.0)\n" > CMakeLists.txt
	printf "project(Hello)\n" >> CMakeLists.txt
	printf "include_directories(lib)\n" >> CMakeLists.txt
	printf "\n" >> CMakeLists.txt
	printf "file(GLOB LIB \"lib/*.cpp\")\n" >> CMakeLists.txt
	printf "add_executable(Hello src/hello.cpp)" >> CMakeLists.txt

clean:
	rm -rf build
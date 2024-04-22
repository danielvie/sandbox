all: default

i: init

m: create_main

c: clean

default:
	cmake -B ./build
	cmake --build ./build
	./build/main

init: create_cmake
init: create_folders
init: create_main

create_cmake:
	printf "cmake_minimum_required(VERSION 3.20.0)\n" > CMakeLists.txt
	printf "project(Main)\n" >> CMakeLists.txt
	printf "\n" >> CMakeLists.txt
	printf "set(CMAKE_CXX_STANDARD 17)\n" >> CMakeLists.txt
	printf "\n" >> CMakeLists.txt
	printf "include_directories(fun)\n" >> CMakeLists.txt
	printf "include_directories(src)\n" >> CMakeLists.txt
	printf "\n" >> CMakeLists.txt
	printf "file(GLOB mySources CONFIGURE_DEPENDS "src/*.cpp" "fun/*.cpp") >> CMakeLists.txt
	printf "add_executable(Main src/main.cpp)" >> CMakeLists.txt

create_folders:
	mkdir fun
	mkdir build
	mkdir src

create_main:
	printf "#include <iostream>\n" > src/main.cpp
	printf "\n" >> src/main.cpp
	printf "int main(int argc, char const *argv[])\n" >> src/main.cpp
	printf "{\n" >> src/main.cpp
	printf "	std::cout << \"hello\" << std::endl;\n" >> src/main.cpp
	printf "}\n" >> src/main.cpp

clean:
	rm -rf build

purge:
	rm -rf build
	rm -rf fun
	rm -rf src
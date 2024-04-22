CXXFLAGS=-std=c++20 -I../tools
CXX=g++-11.2.0

all: main

main: main.cpp Makefile
	$(CXX) $(CXXFLAGS) -o main main.cpp

clean:
	@rm -f -- main

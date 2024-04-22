CXXFLAGS=-std=c++20
CXXFLAGS += -fconcepts-diagnostics-depth=1
CXX=g++-11.2.0

all: main

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

clean:
	@rm -f -- main

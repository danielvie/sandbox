CXXFLAGS=-std=c++20 -fconcepts-diagnostics-depth=2 -I ../tools
CXX=g++-11.2.0

ALL= main

all: $(ALL)

main: main.cpp chrono_helper.h
	$(CXX) $(CXXFLAGS) -o main main.cpp

clean:
	@rm -f -- $(ALL)

CXXFLAGS=-I../tools
CXX=g++-11.2.0

ALL=main_17 main_20

all: $(ALL)

main_17: main.cpp Makefile
	$(CXX) -std=c++17 $(CXXFLAGS) -o main_17 main.cpp

main_20: main.cpp Makefile
	$(CXX) -std=c++20 $(CXXFLAGS) -o main_20 main.cpp

clean:
	@rm -f -- $(ALL)

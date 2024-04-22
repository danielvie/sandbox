CXXFLAGS=-std=c++20 -fconcepts-diagnostics-depth=2 -I ../tools
CXX=g++-11.2.0

ALL= main rai requires indirectly

all: $(ALL)

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

rai: rai.cpp
	$(CXX) $(CXXFLAGS) -o rai rai.cpp

requires: requires.cpp
	$(CXX) $(CXXFLAGS) -o requires requires.cpp

indirectly: indirectly.cpp
	$(CXX) $(CXXFLAGS) -o indirectly indirectly.cpp

clean:
	@rm -f -- $(ALL)

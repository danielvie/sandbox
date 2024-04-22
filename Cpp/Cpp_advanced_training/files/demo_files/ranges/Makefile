CXXFLAGS=-std=c++20
CXX=g++-11.2.0

ALL= main sort
all: $(ALL)

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

sort: sort.cpp
	$(CXX) $(CXXFLAGS) -o sort sort.cpp

clean:
	@rm -f -- $(ALL)

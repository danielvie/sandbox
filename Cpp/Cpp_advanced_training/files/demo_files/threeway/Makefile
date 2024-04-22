CXXFLAGS=-std=c++20 -I../tools -Wpedantic
CXX=g++-11.2.0

ALL= main
all: $(ALL)

main: main.cpp Makefile
	$(CXX) $(CXXFLAGS) -o main main.cpp

clean:
	@rm -f -- $(ALL)

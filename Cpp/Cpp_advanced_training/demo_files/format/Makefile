FMT_INC=-I/usr/local/include
LIBFMT=-L /usr/local/gcc-11.2.0/lib64 -lfmt
CXXFLAGS=-I../tools
CXXFLAGS+= -fconcepts-ts -std=c++20
CXXFLAGS+= $(FMT_INC)
CXX=g++-11.2.0

ALL=main
#no:
#	@echo remove to build

all: $(ALL)

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp $(LIBFMT)

clean:
	@rm -f -- $(ALL)

CXXFLAGS=-std=c++20 -I../tools -Wpedantic -Wno-cpp -lpthread
CXX=g++-11.2.0

ALL= main sync sema barrier latch stop_token
all: $(ALL)

main: main.cpp Makefile
	$(CXX) $(CXXFLAGS) -o main main.cpp

stop_token: stop_token.cpp Makefile
	$(CXX) $(CXXFLAGS) -o stop_token stop_token.cpp

sync: sync.cpp Makefile
	$(CXX) $(CXXFLAGS) -o sync sync.cpp

sema: sema.cpp Makefile
	$(CXX) $(CXXFLAGS) -o sema sema.cpp

barrier: barrier.cpp Makefile
	$(CXX) $(CXXFLAGS) -o barrier barrier.cpp

latch: latch.cpp Makefile
	$(CXX) $(CXXFLAGS) -o latch latch.cpp

stop_token: sync_out.h
sema: sync_out.h

clean:
	@rm -f -- $(ALL)

CXX=g++
CXXFLAGS=-std=c++20 -fmodules-ts

all: main

main: roll.o main.o DieSet.o Die.o
	g++-12 -o main roll.o main.o DieSet.o Die.o

main.o: main.cpp roll.cpp Die.h DieSet.h
Die.o: Die.cpp Die.h
DieSet.o: DieSet.cpp DieSet.h Die.h
roll.o: roll.cpp Die.h DieSet.h

clean:
	rm -f *.o
	rm -rf gcm.cache



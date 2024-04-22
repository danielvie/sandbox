SUFFIXES=.o .cpp
GCC=g++
GCCFLAGS= -O
GCCFLAGS= -std=c++11

OBJS=personmain.o Person.o Swimmer.o Typist.o Programmer.o

main = main

all: ${main}
	./${main}

${main}: $(OBJS)
	$(GCC) $(GCCFLAGS) -o main $(OBJS)

clean:
	rm -f $(OBJS) main

.cpp.o:
	$(GCC) $(GCCFLAGS) -c $<

# DO NOT DELETE

personmain.o: personmain.cpp Programmer.h Typist.h Person.h Swimmer.h
Programmer.o: Programmer.cpp Programmer.h Person.h
Typist.o: Typist.cpp Typist.h Person.h
Person.o: Person.cpp Person.h Person.h
Swimmer.o: Swimmer.cpp Swimmer.h Person.h

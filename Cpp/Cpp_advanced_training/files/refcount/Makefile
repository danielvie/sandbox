SUFFIXES=.o .cpp
GCC=g++
GCCFLAGS= -O -std=c++20 -Wall

MAIN=sortword
OBJS=$(MAIN).o

all: r

r: ${MAIN}
	./${MAIN}

$(MAIN): $(OBJS)
	$(GCC) $(GCCFLAGS) -o $(MAIN) $(OBJS)

clean:
	rm -f $(OBJS) $(MAIN)

.cpp.o:
	$(GCC) $(GCCFLAGS) -c $<

# DO NOT DELETE

$(MAIN).o: MyStr.h

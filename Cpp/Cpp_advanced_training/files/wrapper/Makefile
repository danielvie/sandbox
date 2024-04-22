SUFFIXES=.o .cpp
GCC=g++
GCCFLAGS= -O -Wall

MAIN=main
OBJS=$(MAIN).o

all: ${MAIN}
	./${MAIN}


$(MAIN): $(OBJS)
	$(GCC) $(GCCFLAGS) -o $(MAIN) $(OBJS)

clean:
	rm -f $(OBJS) $(MAIN)

.cpp.o:
	$(GCC) $(GCCFLAGS) -c $<

# DO NOT DELETE

$(MAIN).o: rectangle.h

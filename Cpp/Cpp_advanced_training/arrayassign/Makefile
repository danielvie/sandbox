SUFFIXES=.o .cpp
GCC=g++
GCCFLAGS= -O -Wall

MAIN=arraymain
OBJS=$(MAIN).o array.o

$(MAIN): $(OBJS)
	$(GCC) $(GCCFLAGS) -o $(MAIN) $(OBJS)

clean:
	rm -f $(OBJS) $(MAIN)

.cpp.o:
	$(GCC) $(GCCFLAGS) -c $<

# DO NOT DELETE

array.o: array.cpp array.h
arraymain.o: array.h

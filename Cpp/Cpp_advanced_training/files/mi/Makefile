SUFFIXES=.o .cpp
GCC=g++
GCCFLAGS= -O -Wall

MAIN=main
OBJS=$(MAIN).o

$(MAIN): $(OBJS)
	$(GCC) $(GCCFLAGS) -o $(MAIN) $(OBJS)

clean:
	rm -f $(OBJS) $(MAIN)

.cpp.o:
	$(GCC) $(GCCFLAGS) -c $<

# DO NOT DELETE

$(MAIN).o: ownership.h catering.h vehicle.h foodtruck.h

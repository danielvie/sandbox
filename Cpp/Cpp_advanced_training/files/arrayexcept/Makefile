SUFFIXES=.o .cpp
GCC=g++
GCCFLAGS= -O -Wall

MAIN=main
MAIN2=pushmain
OBJS=$(MAIN).o
OBJS2=$(MAIN2).o

default: r1 

r1: $(MAIN)
	./$(MAIN)

r2: $(MAIN2)
	./$(MAIN2)

all: $(MAIN) $(MAIN2)

$(MAIN): $(OBJS)
	$(GCC) $(GCCFLAGS) -o $(MAIN) $(OBJS)

$(MAIN2): $(OBJS2)
	$(GCC) $(GCCFLAGS) -o $(MAIN2) $(OBJS2)

clean:
	rm -f $(OBJS) $(MAIN) $(OBJS2) $(MAIN2)

.cpp.o:
	$(GCC) $(GCCFLAGS) -c $<

# DO NOT DELETE

$(MAIN).o: arraysafe.h
$(MAIN2).o: arraypushsafe.h

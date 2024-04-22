SUFFIXES=.o .cpp
GCC=g++
GCCFLAGS= -O

MAIN2=finditmain
OBJS2=$(MAIN2).o
MAIN=snailitmain
OBJS=$(MAIN).o

$(MAIN): $(OBJS)
	$(GCC) $(GCCFLAGS) -o $(MAIN) $(OBJS)

all: $(MAIN) $(MAIN2)

$(MAIN2): $(OBJS2)
	$(GCC) $(GCCFLAGS) -o $(MAIN2) $(OBJS2)

clean:
	rm -f $(OBJS) $(MAIN) $(OBJS2) $(MAIN2)

.cpp.o:
	$(GCC) $(GCCFLAGS) -c $<

# DO NOT DELETE

$(MAIN).o: snailiter.h
$(MAIN2).o: finditer.h

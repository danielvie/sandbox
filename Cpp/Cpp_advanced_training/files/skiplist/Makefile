SUFFIXES=.o .cpp
GCC=g++
GCCFLAGS= -O -Wall

MAIN=slmain
OBJS=$(MAIN).o
MAIN2=freqmap
OBJS2=$(MAIN2).o
MAIN3=freqsl
OBJS3=$(MAIN3).o

default: $(MAIN) $(MAIN2)

all: $(MAIN) $(MAIN2) $(MAIN3)

$(MAIN): $(OBJS)
	$(GCC) $(GCCFLAGS) -o $(MAIN) $(OBJS)

$(MAIN2): $(OBJS2)
	$(GCC) $(GCCFLAGS) -o $(MAIN2) $(OBJS2)

$(MAIN3): $(OBJS3)
	$(GCC) $(GCCFLAGS) -o $(MAIN3) $(OBJS3)

clean:
	rm -f $(OBJS) $(MAIN) $(MAIN2) $(OBJS2) $(MAIN3) $(OBJS3)

.cpp.o:
	$(GCC) $(GCCFLAGS) -c $<

# DO NOT DELETE

$(MAIN).o: SkipList.h
#$(MAIN2).o: SkipList.h stl_sl.h
$(MAIN3).o: SkipList.h stl_sl.h

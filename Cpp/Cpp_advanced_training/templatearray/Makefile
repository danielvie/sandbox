SUFFIXES=.o .cpp
GCC=g++
GCCFLAGS= -O -Wall

MAIN=arraymain
MAIN2=arraymain2
OBJS=$(MAIN).o
OBJS2=$(MAIN2).o

$(MAIN): $(OBJS)
	$(GCC) $(GCCFLAGS) -o $(MAIN) $(OBJS)

all: $(MAIN) $(MAIN2)

$(MAIN2): $(OBJS2)
	$(GCC) $(GCCFLAGS) -o $(MAIN2) $(OBJS2)

clean:
	rm -f $(OBJS) $(OBJS2) $(MAIN) $(MAIN2)

.cpp.o:
	$(GCC) $(GCCFLAGS) -c $<

# DO NOT DELETE

arraymain.o: array.h
arraymain2.o: array.h

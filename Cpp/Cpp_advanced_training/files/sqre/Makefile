SUFFIXES=.o .cpp
GCC=g++
GCCFLAGS= -O -Wall

MAIN1=sqremaina
OBJS1=$(MAIN1).o
MAIN2=sqremainb
OBJS2=$(MAIN2).o

$(MAIN1): $(OBJS1)
	$(GCC) $(GCCFLAGS) -o $(MAIN1) $(OBJS1)

$(MAIN2): $(OBJS2)
	$(GCC) $(GCCFLAGS) -o $(MAIN2) $(OBJS2)

all: $(MAIN1) $(MAIN2)

clean:
	rm -f $(OBJS1) $(MAIN1)
	rm -f $(OBJS2) $(MAIN2)

.cpp.o:
	$(GCC) $(GCCFLAGS) -c $<

a: ${MAIN1}
	./${MAIN1}

b: ${MAIN2}
	./${MAIN2}


# DO NOT DELETE

sqremaina.o: sum.h sqrefunc.h
sqremainb.o: sum.h 

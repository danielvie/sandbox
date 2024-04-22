SUFFIXES=.o .cpp
GCC=g++
GCCFLAGS= -O -Wall

MAIN=filtmain
OBJS=$(MAIN).o 
MAIN2=filtmain2
OBJS2=$(MAIN2).o 
HEADERS=uppercase.h reverse.h
HEADERS2=$(HEADERS) tr.h

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

$(MAIN): $(HEADERS)
$(MAIN2): $(HEADERS2)

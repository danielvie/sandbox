SUFFIXES=.o .cpp
GCC=g++
GCCFLAGS= -O

MAIN=virtfuncs
OBJS=$(MAIN).o

all: r

$(MAIN): $(OBJS)
	$(GCC) $(GCCFLAGS) -o $(MAIN) $(OBJS)

clean:
	rm -f $(OBJS) $(MAIN)

.cpp.o:
	$(GCC) $(GCCFLAGS) -c $<

# DO NOT DELETE

r: ${MAIN}
	./${MAIN}

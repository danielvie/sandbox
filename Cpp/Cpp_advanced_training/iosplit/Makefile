SUFFIXES=.o .cpp

GCC=g++
GCCFLAGS= -O -Wall

OBJS=try.o iosplit.o
try: $(OBJS)
	$(GCC) $(GCCFLAGS) -o try $(OBJS)

clean:
	rm -f $(OBJS) try aap noot

.cpp.o:
	$(GCC) $(GCCFLAGS) -c $<
# DO NOT DELETE
iosplit.o: iosplit.h
try.o: iosplit.h

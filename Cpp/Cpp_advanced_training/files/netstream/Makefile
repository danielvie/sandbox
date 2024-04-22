SUFFIXES=.o .cpp
GCC=g++

OBJS1=try.o netstream.o
OBJS2=try2.o netstream2.o
OBJS=$(OBJS1) $(OBJS2)

all:	try2
# try is niet meer volgens de standaard.

try: $(OBJS1)
	$(GCC) -g -o try $(OBJS1) # -lsocket -lnsl

try2: $(OBJS2)
	$(GCC) -g -o try2 $(OBJS2) # -lsocket -lnsl

.cpp.o:
	$(GCC) -g -c $<

clean:
	rm -f try try2 $(OBJS)

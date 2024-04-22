CC=g++
CFLAGS=-Wall -std=c++11
LDFLAGS=-shared

SRCS=HelloWorld.cpp
OBJS=$(SRCS:.cpp=.o)

TARGET=HelloWorld.dll

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

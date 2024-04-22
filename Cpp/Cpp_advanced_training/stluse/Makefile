CXXFLAGS += -Wall
CXXFLAGS += -std=c++17

TARGETS=maina mainb mainc maind

all: $(TARGETS)

maina:	maina.cpp
	g++ $(CXXFLAGS) maina.cpp -o maina

mainb:	mainb.cpp
	g++ $(CXXFLAGS) mainb.cpp -o mainb

mainc:	mainc.cpp
	g++ $(CXXFLAGS) mainc.cpp -o mainc

maind:	maind.cpp
	g++ $(CXXFLAGS) maind.cpp -o maind

clean:
	rm -f $(TARGETS)

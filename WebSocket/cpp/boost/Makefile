CXX = g++
BOOST_DIR = /opt/homebrew/Cellar/boost@1.76/1.76.0_2
CXXFLAGS = -std=c++17 -I$(BOOST_DIR)/include
LDFLAGS = -L$(BOOST_DIR)/lib -lboost_system -DBOOST_BEAST_ALLOW_DEPRECATED

all: r

r: b
r: run

b: websocket_client

run:
	./websocket_client

websocket_client: src/client_boost.cpp 
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)
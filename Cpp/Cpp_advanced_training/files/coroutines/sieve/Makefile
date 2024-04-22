all: sieve
	./sieve

sieve: sieve.cpp
	g++ -std=c++20 sieve.cpp -o sieve

# initialize libcoro for the generators
i:
	git clone https://github.com/jbaldwin/libcoro.git
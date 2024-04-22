default: build

b: build

c: clean

r: run

build:
	cmake -B ./build
	cmake --build ./build

run:
	./build/unittest

clean:
	rm -rf build

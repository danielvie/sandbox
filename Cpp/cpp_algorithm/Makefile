
app = transform

all: default

i: init

m: create_main

c: clean

default:
	cmake -B ./build
	cmake --build ./build
	./build/${app}

clean:
	rm -rf build

default: br

br: b
br: r

r:
	python test_extension.py

b:
	cmake -B build
	cmake --build build
	
c:
	rm -rf build
	rm -rf extension.so
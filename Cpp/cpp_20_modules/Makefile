CXX = clang++ -std=c++20

a:
	$(CXX) -o split.pcm --precompile -x c++-module maths.cpp

b:
	$(CXX) -o main -fprebuilt-module-path=. main.cpp maths.cpp

clean:
	rm *.o
	rm *.pcm
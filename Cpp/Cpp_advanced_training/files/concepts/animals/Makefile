CXXFLAGS=-std=c++20 -fconcepts-diagnostics-depth=2 -I ~/demo_files/tools
CXX=g++

ALL= animals

# all: $(ALL)
all: r

animals: animals.cpp animals.h pet_funcs.h pet_concepts.h
	$(CXX) $(CXXFLAGS) -o animals animals.cpp

r: ${ALL}
	./${ALL}


clean:
	@rm -f -- $(ALL)

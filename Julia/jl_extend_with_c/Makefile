INCLUDE = -I/Users/danielvieira/.julia/juliaup/julia-1.10.0+0.aarch64.apple.darwin14/include/julia 
LIB = -L/Users/danielvieira/.julia/juliaup/julia-1.10.0+0.aarch64.apple.darwin14/lib

all: r


b: 
	gcc -fPIC -shared -o mysum.so mysum.c $(INCLUDE) $(LIB) -ljulia
	
r: 
	julia mysum_script.jl

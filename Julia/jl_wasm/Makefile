r:
	julia test.jl
	
b:
	emcc julia_function.jl -o julia_function.js \
		--pre-js pre.js \
		--post-js post.js \
		-s EXPORTED_FUNCTIONS="['_add_numbers']" \
		-s EXPORTED_RUNTIME_METHODS="['cwrap']"
all: r

i:
	cargo init

r:
	cargo run
	
w:
	wasm-pack build --target web

# w:
# 	em++ -O3 -s SIDE_MODULE=1 -o cpp_fun.wasm cpp/cpp_fun.cpp
# 	wasm-pack build --target web

s:
	python -m http.server
	
em:
	em++ -O3 -s SIDE_MODULE=1 -o cpp_fun.wasm cpp/cpp_fun.cpp
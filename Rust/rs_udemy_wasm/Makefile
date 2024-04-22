all: b

i:
	cargo init

r:
	cargo run
	
	
b:
	wasm-pack build --target web
	
buildw:
	emcc c_wasm/add.c -o www/public/add.wasm -s EXPORTED_FUNCTIONS="['_add']" --no-entry
r:
	bun run test.js
	
wasm:
	zig build-lib math.zig -target wasm32-freestanding -dynamic -rdynamic

clean:
	rm -rf *.o
	rm -rf *.wasm
	rm fib
	rm math
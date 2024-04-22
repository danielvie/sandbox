all: r

c:
	gcc soma.c -o soma
	./soma

r:
	zig build-exe main.zig -lc -freference-trace
	./main	
	
translate:
	zig translate-c soma.c > soma.zig

t:
	zig test main.zig

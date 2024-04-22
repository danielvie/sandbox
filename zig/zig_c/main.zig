const std = @import("std");
const c = @cImport({
    @cInclude("/Users/danielvieira/Sandbox/zig/zig_c/soma.c");
});

pub fn soma2(a: i32, b: i32) i32 {
    return a + b;
}

pub fn soma3(a: i32, b: i32) i32 {
    return c.soma(a, b);
}

pub fn main() void {
    const a: i32 = 5;
    const b: i32 = 7;
    const soma: i32 = c.soma(a, b);
    const sub: i32 = c.sub(a, b);
    const mul: i32 = c.mul(a, b);

    const res = a + b;

    std.debug.print("{} e {} -> soma: {}, sub: {}, mul: {}, res: {}\n", .{ a, b, soma, sub, mul, res });

    std.debug.print("\n\n==========================\n", .{});
    std.debug.print("==========================\n", .{});
    std.debug.print("Soma3: {}\n", .{soma3(a, b)});
    std.debug.print("==========================\n", .{});
}

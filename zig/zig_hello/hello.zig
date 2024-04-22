const std = @import("std");
const ArrayList = std.ArrayList;
const assert = std.debug.assert;

fn soma(a: i32, b: i32) i32 {
    return a + b;
}

fn sub(a: i32, b: i32) i32 {
    return a - b;
}

fn mul(a: i32, b: i32) i32 {
    return a * b;
}

fn div(a: i32, b: i32) ?i32 {
    if (b == 0) return null;
    return @divTrunc(a, b);
}

// tests
test "add" {
    assert(soma(3, 4) == 7);
    assert(soma(-1, 5) == 4);
    assert(soma(0, 0) == 0);
}

test "div" {
    assert(div(4, 4) == 1);
    assert(div(5, 2) == 2);
    assert(div(0, 0) == null);
}

pub fn main() void {
    const a: i32 = 2;
    const b: i32 = 5;

    const result = soma(a, b);
    std.debug.print("meu hello, World! The sum of {} and {} is {}\n", .{ a, b, result });

    var numbers: [5]i32 = [5]i32{ 1, 2, 3, 4, 5 };

    var sum: i32 = 0;
    for (numbers) |number| {
        sum += number;
    }

    std.debug.print("sum: {}\n", .{sum});

    std.debug.print("Elements:\n", .{});
    for (numbers) |number| {
        std.debug.print("{}\n", .{number});
    }

    std.debug.print("Alocator\n", .{});

    var allocator = std.heap.page_allocator;

    // Equivalent of A = []
    var A = ArrayList(i32).init(allocator);
    defer A.deinit();

    // Equivalent of A.append(1) and A.append(2)
    A.append(1) catch unreachable;
    A.append(2) catch unreachable;
    A.append(2) catch unreachable;
    A.append(2) catch unreachable;
    A.append(2) catch unreachable;

    assert(A.items.len == 5);

    std.debug.print("bla:::{} \n", .{A.items.len});

    // Equivalent of the for loop
    for (A.items) |ai| {
        std.debug.print("{}\n", .{ai});
    }
}

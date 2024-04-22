const std = @import("std");

const Result = union(enum) {
    int: i32,
    string: []const u8,
    float: f32,
};

fn calculate(input: u8) Result {
    return switch (input) {
        0 => Result{ .int = 30 },
        1 => Result{ .float = 3.1415 },
        else => Result{ .string = "Hello" },
    };
}

pub fn main() anyerror!void {
    const result = calculate(2);

    switch (result) {
        .int => |value| std.log.info("Int value {}", .{value}),
        .float => |value| std.log.info("Float value {}", .{value}),
        .string => |value| std.log.info("String value {s}", .{value}),
    }

    // std.log.info("{any}", .{result.float});
    std.log.info("Size of result: {}", .{@sizeOf(Result)});
}

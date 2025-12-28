const std = @import("std");

pub fn addNullByte(allocator: std.mem.Allocator, bytes: []const u8) ![:0]u8 {
    const buf = try allocator.alloc(u8, bytes.len + 1);
    std.mem.copyForwards(u8, buf[0..bytes.len], bytes);
    buf[bytes.len] = 0;
    return buf[0..bytes.len :0];
}

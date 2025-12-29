const std = @import("std");
const ur = @import("../ur.zig");

pub const Rect = struct {
    x: i32,
    y: i32,
    w: i32,
    h: i32,
};

pub fn screenRectForPlayer(player_x: f64, player_y: f64) Rect {
    var rect = Rect{
        .x = @intCast(@as(i64, @intFromFloat(player_x * @as(f64, @floatFromInt(ur.tile_width)))) - (ur.screen_width / 2)),
        .y = @intCast(@as(i64, @intFromFloat(player_y * @as(f64, @floatFromInt(ur.tile_height)))) - (ur.screen_height / 2)),
        .w = ur.screen_width,
        .h = ur.screen_height,
    };

    if (rect.x <= 0) rect.x = 0;
    if (rect.x >= ur.screen_width * 2) rect.x = ur.screen_width * 2;
    if (rect.y <= 0) rect.y = 0;
    if (rect.y >= ur.screen_height * 2) rect.y = ur.screen_height * 2;

    return rect;
}

test "map math clamps screen rect" {
    const rect = screenRectForPlayer(0.0, 0.0);
    try std.testing.expectEqual(@as(i32, 0), rect.x);
    try std.testing.expectEqual(@as(i32, 0), rect.y);

    const rect2 = screenRectForPlayer(1000.0, 1000.0);
    try std.testing.expectEqual(ur.screen_width * 2, rect2.x);
    try std.testing.expectEqual(ur.screen_height * 2, rect2.y);
}

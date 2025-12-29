const std = @import("std");
const ur = @import("../ur.zig");

pub const Rect = struct {
    x: i32,
    y: i32,
    w: i32,
    h: i32,
};

pub const VisibleRange = struct {
    begin_x: i32,
    end_x: i32,
    begin_y: i32,
    end_y: i32,
};

pub fn visibleRange(screen: Rect) VisibleRange {
    const begin_y = @divTrunc(screen.y, ur.tile_height);
    const begin_x = @divTrunc(screen.x, ur.tile_width);

    var end_y = begin_y + @divTrunc(ur.screen_height, ur.tile_height);
    var end_x = begin_x + @divTrunc(ur.screen_width, ur.tile_width);

    end_x += 2;
    end_y += 2;

    return .{ .begin_x = begin_x, .end_x = end_x, .begin_y = begin_y, .end_y = end_y };
}

pub fn tileSrcRect(graphic_index: i32, anim_pos: i32) Rect {
    return .{
        .x = ur.tile_width * graphic_index,
        .y = ur.tile_height * anim_pos,
        .w = ur.tile_width,
        .h = ur.tile_height,
    };
}

pub fn tileDestRect(x: i32, y: i32) Rect {
    return .{
        .x = ur.tile_width * x,
        .y = ur.tile_height * y,
        .w = ur.tile_width,
        .h = ur.tile_height,
    };
}

test "layer math visible range and rects" {
    const screen = Rect{ .x = 64, .y = 32, .w = ur.screen_width, .h = ur.screen_height };
    const range = visibleRange(screen);
    try std.testing.expectEqual(@as(i32, 2), range.begin_x);
    try std.testing.expectEqual(@as(i32, 1), range.begin_y);

    const src = tileSrcRect(3, 2);
    try std.testing.expectEqual(@as(i32, 96), src.x);
    try std.testing.expectEqual(@as(i32, 64), src.y);

    const dst = tileDestRect(5, 7);
    try std.testing.expectEqual(@as(i32, 160), dst.x);
    try std.testing.expectEqual(@as(i32, 224), dst.y);
}

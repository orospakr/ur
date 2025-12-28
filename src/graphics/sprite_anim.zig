const ur = @import("../ur.zig");
const input = @import("../input/input.zig");

pub const Rect = struct {
    x: i32,
    y: i32,
    w: i32,
    h: i32,
};

pub fn animRect(direction: input.Direction, anim: ur.Anim, phase: i64) Rect {
    const phase_i32: i32 = @intCast(phase);
    var result = Rect{
        .w = ur.tile_width,
        .h = ur.tile_height,
        .x = ur.tile_width * 5 + (ur.tile_width * phase_i32),
        .y = 0,
    };

    switch (anim) {
        .walk => result.y = 0,
        .wait => result.y = ur.tile_height * 8,
        else => result.y = 0,
    }

    switch (direction) {
        .north => result.y += ur.tile_height * 0,
        .south => result.y += ur.tile_height * 1,
        .east => result.y += ur.tile_height * 2,
        .west => result.y += ur.tile_height * 3,
        .north_east => result.y += ur.tile_height * 4,
        .north_west => result.y += ur.tile_height * 5,
        .south_east => result.y += ur.tile_height * 6,
        .south_west => result.y += ur.tile_height * 7,
        .none => result.y += ur.tile_height * 1,
    }

    return result;
}

pub fn portraitRect() Rect {
    return .{
        .w = ur.tile_width * 5,
        .h = ur.tile_height * 8,
        .x = 0,
        .y = 0,
    };
}

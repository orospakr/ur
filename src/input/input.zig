const std = @import("std");

pub const Direction = enum {
    none,
    north,
    south,
    west,
    east,
    north_east,
    north_west,
    south_east,
    south_west,
};

pub const Keypad = enum {
    left,
    right,
    up,
    down,
    start,
    select,
    action,
    cancel,
    none,
};

pub const InputState = struct {
    up: bool = false,
    down: bool = false,
    left: bool = false,
    right: bool = false,
    start: bool = false,
    select: bool = false,
    action: bool = false,
    cancel: bool = false,
};

pub fn directionFromInput(input: InputState) Direction {
    if (input.up and input.right) return .north_east;
    if (input.up and input.left) return .north_west;
    if (input.down and input.right) return .south_east;
    if (input.down and input.left) return .south_west;
    if (input.up) return .north;
    if (input.down) return .south;
    if (input.left) return .west;
    if (input.right) return .east;
    return .none;
}

const testing = std.testing;

test "directionFromInput respects diagonals and cardinals" {
    try testing.expectEqual(Direction.north_east, directionFromInput(.{ .up = true, .right = true }));
    try testing.expectEqual(Direction.south_west, directionFromInput(.{ .down = true, .left = true }));
    try testing.expectEqual(Direction.north, directionFromInput(.{ .up = true }));
    try testing.expectEqual(Direction.west, directionFromInput(.{ .left = true }));
    try testing.expectEqual(Direction.none, directionFromInput(.{}));
}

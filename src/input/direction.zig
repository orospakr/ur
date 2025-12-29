const vector2d = @import("../graphics/vector2d.zig");
const input = @import("input.zig");

pub fn directionFromVector(vector: vector2d.Vector2D) input.Direction {
    if (vector.x == 0 and vector.y == 0) return .none;

    if (vector.x == 0) {
        if (vector.y > 0) return .south;
        return .north;
    }

    if (vector.y == 0) {
        if (vector.x > 0) return .east;
        return .west;
    }

    if (vector.x > 0) {
        if (vector.y > 0) return .south_east;
        return .north_east;
    } else {
        if (vector.y > 0) return .south_west;
        return .north_west;
    }
}

pub fn vectorFromDirection(direction: input.Direction) vector2d.Vector2D {
    switch (direction) {
        .north => return vector2d.Vector2D.init(0, -1),
        .south => return vector2d.Vector2D.init(0, 1),
        .east => return vector2d.Vector2D.init(1, 0),
        .west => return vector2d.Vector2D.init(-1, 0),
        .north_east => return vector2d.Vector2D.init(1, -1).normalize(),
        .north_west => return vector2d.Vector2D.init(-1, -1).normalize(),
        .south_east => return vector2d.Vector2D.init(1, 1).normalize(),
        .south_west => return vector2d.Vector2D.init(-1, 1).normalize(),
        .none => return vector2d.Vector2D.init(0, 0),
    }
}

test "direction from vector and back" {
    const std = @import("std");
    const v1 = vector2d.Vector2D.init(0, -5);
    try std.testing.expectEqual(input.Direction.north, directionFromVector(v1));

    const v2 = vector2d.Vector2D.init(2, 3);
    try std.testing.expectEqual(input.Direction.south_east, directionFromVector(v2));

    const v3 = vectorFromDirection(.north_west);
    try std.testing.expectApproxEqAbs(@as(f64, -0.70710678), v3.x, 0.00001);
    try std.testing.expectApproxEqAbs(@as(f64, -0.70710678), v3.y, 0.00001);
}

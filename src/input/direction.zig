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

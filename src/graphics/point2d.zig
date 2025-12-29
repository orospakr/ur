const vector2d = @import("vector2d.zig");

pub const Point2D = struct {
    x: f64,
    y: f64,

    pub fn init(x: f64, y: f64) Point2D {
        return .{ .x = x, .y = y };
    }

    pub fn add(self: Point2D, other: Point2D) Point2D {
        return .{ .x = self.x + other.x, .y = self.y + other.y };
    }

    pub fn sub(self: Point2D, other: Point2D) Point2D {
        return .{ .x = self.x - other.x, .y = self.y - other.y };
    }

    pub fn addVector(self: Point2D, other: vector2d.Vector2D) Point2D {
        return .{ .x = self.x + other.x, .y = self.y + other.y };
    }
};

test "point2d operations" {
    const std = @import("std");
    const a = Point2D.init(1.0, 2.0);
    const b = Point2D.init(3.0, 4.0);
    const sum = a.add(b);
    try std.testing.expectEqual(@as(f64, 4.0), sum.x);
    try std.testing.expectEqual(@as(f64, 6.0), sum.y);

    const delta = a.sub(b);
    try std.testing.expectEqual(@as(f64, -2.0), delta.x);
    try std.testing.expectEqual(@as(f64, -2.0), delta.y);

    const v = vector2d.Vector2D.init(-1.0, 5.0);
    const moved = a.addVector(v);
    try std.testing.expectEqual(@as(f64, 0.0), moved.x);
    try std.testing.expectEqual(@as(f64, 7.0), moved.y);
}

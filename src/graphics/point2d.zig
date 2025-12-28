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

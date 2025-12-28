const std = @import("std");

pub const Vector2D = struct {
    x: f64,
    y: f64,

    pub fn init(x: f64, y: f64) Vector2D {
        return .{ .x = x, .y = y };
    }

    pub fn add(self: Vector2D, other: Vector2D) Vector2D {
        return .{ .x = self.x + other.x, .y = self.y + other.y };
    }

    pub fn sub(self: Vector2D, other: Vector2D) Vector2D {
        return .{ .x = self.x - other.x, .y = self.y - other.y };
    }

    pub fn mul(self: Vector2D, scalar: f64) Vector2D {
        return .{ .x = self.x * scalar, .y = self.y * scalar };
    }

    pub fn div(self: Vector2D, scalar: f64) Vector2D {
        return .{ .x = self.x / scalar, .y = self.y / scalar };
    }

    pub fn length(self: Vector2D) f64 {
        return std.math.sqrt(self.x * self.x + self.y * self.y);
    }

    pub fn normalize(self: Vector2D) Vector2D {
        const len = self.length();
        if (len != 0.0) return self.div(len);
        return self;
    }

    pub fn slope(self: Vector2D) f64 {
        return self.y / self.x;
    }
};

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

test "vector2d math and normalization" {
    const a = Vector2D.init(3.0, 4.0);
    try std.testing.expectEqual(@as(f64, 5.0), a.length());

    const b = Vector2D.init(-1.0, 2.0);
    const sum = a.add(b);
    try std.testing.expectEqual(@as(f64, 2.0), sum.x);
    try std.testing.expectEqual(@as(f64, 6.0), sum.y);

    const scaled = a.mul(2.0);
    try std.testing.expectEqual(@as(f64, 6.0), scaled.x);
    try std.testing.expectEqual(@as(f64, 8.0), scaled.y);

    const unit = a.normalize();
    try std.testing.expectApproxEqAbs(@as(f64, 1.0), unit.length(), 0.000001);
}

test "vector2d slope and zero normalization" {
    const a = Vector2D.init(2.0, 6.0);
    try std.testing.expectEqual(@as(f64, 3.0), a.slope());

    const zero = Vector2D.init(0.0, 0.0);
    const normalized = zero.normalize();
    try std.testing.expectEqual(@as(f64, 0.0), normalized.x);
    try std.testing.expectEqual(@as(f64, 0.0), normalized.y);
}

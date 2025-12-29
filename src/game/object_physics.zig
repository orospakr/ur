const std = @import("std");
const ur = @import("../ur.zig");
const vector2d = @import("../graphics/vector2d.zig");
const point2d = @import("../graphics/point2d.zig");

pub const MovementState = struct {
    position: point2d.Point2D,
    velocity: vector2d.Vector2D,
};

pub fn step(state: MovementState, direction_input: vector2d.Vector2D) MovementState {
    const accel: f64 = 0.05;
    const velmax: f64 = 0.2;

    const acceleration = direction_input.normalize().mul(accel);

    var velocity = state.velocity.add(acceleration);
    if (velocity.length() > velmax) {
        velocity = velocity.normalize().mul(velmax);
    }

    velocity = velocity.mul(0.9);

    var position = state.position;

    if (position.x < 0) {
        position.x = 0;
        velocity.x = 0;
    } else if (position.x > @as(f64, @floatFromInt(ur.map_width - 1))) {
        position.x = @as(f64, @floatFromInt(ur.map_width - 1));
        velocity.x = 0;
    }

    if (position.y < 0) {
        position.y = 0;
        velocity.y = 0;
    } else if (position.y > @as(f64, @floatFromInt(ur.map_height - 1))) {
        position.y = @as(f64, @floatFromInt(ur.map_height - 1));
        velocity.y = 0;
    }

    position = position.addVector(velocity);

    return .{ .position = position, .velocity = velocity };
}

test "object physics step from rest" {
    const state = MovementState{
        .position = point2d.Point2D.init(10.0, 10.0),
        .velocity = vector2d.Vector2D.init(0, 0),
    };
    const direction_input = vector2d.Vector2D.init(1, 0);
    const next = step(state, direction_input);

    try std.testing.expectApproxEqAbs(@as(f64, 0.045), next.velocity.x, 0.000001);
    try std.testing.expectApproxEqAbs(@as(f64, 10.045), next.position.x, 0.000001);
    try std.testing.expectApproxEqAbs(@as(f64, 10.0), next.position.y, 0.000001);
}

test "object physics clamps bounds" {
    const state = MovementState{
        .position = point2d.Point2D.init(-1.0, 200.0),
        .velocity = vector2d.Vector2D.init(0.5, -0.5),
    };
    const next = step(state, vector2d.Vector2D.init(0, 0));

    try std.testing.expectEqual(@as(f64, 0.0), next.position.x);
    try std.testing.expectEqual(@as(f64, @floatFromInt(ur.map_height - 1)), next.position.y);
    try std.testing.expectEqual(@as(f64, 0.0), next.velocity.x);
    try std.testing.expectEqual(@as(f64, 0.0), next.velocity.y);
}

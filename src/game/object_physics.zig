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

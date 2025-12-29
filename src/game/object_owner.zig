const vector2d = @import("../graphics/vector2d.zig");

pub const CollisionResult = struct {
    pub const Axis = enum(u2) {
        none = 0,
        vertical = 1,
        horizontal = 2,
        both = 3,
    };

    collided_on: Axis = .none,
    clamped_vector: vector2d.Vector2D = vector2d.Vector2D.init(0, 0),
    tile_type_idx: i32 = 0,
    tile_type: ?*const anyopaque = null,
};

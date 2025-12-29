const std = @import("std");
const SDL = @import("sdl2");
const ur = @import("../ur.zig");
const layer_math = @import("layer_math.zig");
const point2d = @import("../graphics/point2d.zig");
const vector2d = @import("../graphics/vector2d.zig");
const object_owner = @import("../game/object_owner.zig");
const object_mod = @import("../game/object.zig");

pub const TileType = struct {
    graphic_index: i32,
    solid: bool,
};

pub const Layer = struct {
    tilepile: *SDL.SDL_Texture,
    tiles_anim_pos: i64 = 0,
    tiles: []const i32,
    tile_types: []const TileType,
    map_width: i32,
    map_height: i32,
    registered_objects: std.ArrayListUnmanaged(*object_mod.Object) = .empty,

    pub fn init(
        tilepile: *SDL.SDL_Texture,
        tiles: []const i32,
        tile_types: []const TileType,
        map_width: i32,
        map_height: i32,
    ) Layer {
        return .{
            .tilepile = tilepile,
            .tiles = tiles,
            .tile_types = tile_types,
            .map_width = map_width,
            .map_height = map_height,
        };
    }

    pub fn deinit(self: *Layer, allocator: std.mem.Allocator) void {
        self.registered_objects.deinit(allocator);
    }

    pub fn advanceAnimation(self: *Layer) void {
        self.tiles_anim_pos = @intCast(SDL.SDL_GetTicks() / 33 / 3 % 8);
    }

    pub fn draw(self: *Layer, renderer: *SDL.SDL_Renderer, screen_geom: SDL.SDL_Rect) void {
        const screen = layer_math.Rect{
            .x = screen_geom.x,
            .y = screen_geom.y,
            .w = screen_geom.w,
            .h = screen_geom.h,
        };

        const range = layer_math.visibleRange(screen);
        var y: i32 = range.begin_y;
        while (y < range.end_y) : (y += 1) {
            var x: i32 = range.begin_x;
            while (x < range.end_x) : (x += 1) {
                if (x < 0 or y < 0 or x >= self.map_width or y >= self.map_height) continue;

                const idx: usize = @intCast(x + y * self.map_width);
                if (idx >= self.tiles.len) continue;

                const tile_index = self.tiles[idx];
                if (tile_index < 0 or tile_index >= self.tile_types.len) continue;

                const tile_type = self.tile_types[@intCast(tile_index)];
                const src = layer_math.tileSrcRect(tile_type.graphic_index, @intCast(self.tiles_anim_pos));
                const dst = layer_math.tileDestRect(x, y);

                var src_rect = SDL.SDL_Rect{ .x = src.x, .y = src.y, .w = src.w, .h = src.h };
                var dst_rect = SDL.SDL_Rect{
                    .x = dst.x - screen_geom.x,
                    .y = dst.y - screen_geom.y,
                    .w = dst.w,
                    .h = dst.h,
                };

                _ = SDL.SDL_RenderCopy(renderer, self.tilepile, &src_rect, &dst_rect);
            }
        }
    }

    pub fn registerObject(self: *Layer, allocator: std.mem.Allocator, obj: *object_mod.Object) !void {
        try self.registered_objects.append(allocator, obj);
    }

    pub fn checkMapPathCollision(
        self: *Layer,
        position: point2d.Point2D,
        velocity: vector2d.Vector2D,
    ) object_owner.CollisionResult {
        const length = velocity.length();
        if (length == 0) return .{ .collided_on = .none, .clamped_vector = velocity };

        const epsilon: f64 = 0.02;
        const dir = velocity.normalize();

        var step: f64 = 0.0;
        while (step <= length) : (step += epsilon) {
            const test_point = point2d.Point2D.init(
                position.x + dir.x * step,
                position.y + dir.y * step,
            );

            const tile_x = @as(i32, @intFromFloat(test_point.x));
            const tile_y = @as(i32, @intFromFloat(test_point.y));
            if (tile_x < 0 or tile_y < 0 or tile_x >= self.map_width or tile_y >= self.map_height) {
                continue;
            }

            const idx: usize = @intCast(tile_x + tile_y * self.map_width);
            if (idx >= self.tiles.len) continue;

            const tile_index = self.tiles[idx];
            if (tile_index < 0 or tile_index >= self.tile_types.len) continue;

            const tile_type = &self.tile_types[@intCast(tile_index)];
            if (tile_type.solid) {
                var axis: object_owner.CollisionResult.Axis = .none;
                if (velocity.x != 0) axis = .horizontal;
                if (velocity.y != 0) axis = if (axis == .horizontal) .both else .vertical;

                return .{
                    .collided_on = axis,
                    .clamped_vector = velocity,
                    .tile_type_idx = tile_index,
                    .tile_type = @ptrCast(tile_type),
                };
            }
        }

        // Ensure the end point is checked even if the step loop skips it.
        const end_point = point2d.Point2D.init(position.x + velocity.x, position.y + velocity.y);
        const end_x = @as(i32, @intFromFloat(end_point.x));
        const end_y = @as(i32, @intFromFloat(end_point.y));
        if (end_x >= 0 and end_y >= 0 and end_x < self.map_width and end_y < self.map_height) {
            const end_idx: usize = @intCast(end_x + end_y * self.map_width);
            if (end_idx < self.tiles.len) {
                const end_tile_index = self.tiles[end_idx];
                if (end_tile_index >= 0 and end_tile_index < self.tile_types.len) {
                    const end_tile = &self.tile_types[@intCast(end_tile_index)];
                    if (end_tile.solid) {
                        var axis: object_owner.CollisionResult.Axis = .none;
                        if (velocity.x != 0) axis = .horizontal;
                        if (velocity.y != 0) axis = if (axis == .horizontal) .both else .vertical;
                        return .{
                            .collided_on = axis,
                            .clamped_vector = velocity,
                            .tile_type_idx = end_tile_index,
                            .tile_type = @ptrCast(end_tile),
                        };
                    }
                }
            }
        }

        return .{ .collided_on = .none, .clamped_vector = velocity };
    }
};

test "layer registers objects and detects solid tile" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    const dummy_tex: *SDL.SDL_Texture = @ptrFromInt(1);
    const tile_types = [_]TileType{
        .{ .graphic_index = 0, .solid = false },
        .{ .graphic_index = 1, .solid = true },
    };
    const tiles = [_]i32{ 0, 1, 0, 0 };
    var layer = Layer.init(dummy_tex, tiles[0..], tile_types[0..], 2, 2);
    defer layer.deinit(allocator);

    var obj = object_mod.Object{
        .sprite = undefined,
        .name = "test",
    };
    try layer.registerObject(allocator, &obj);
    try std.testing.expectEqual(@as(usize, 1), layer.registered_objects.items.len);

    const result = layer.checkMapPathCollision(
        point2d.Point2D.init(0.0, 0.0),
        vector2d.Vector2D.init(1.0, 0.0),
    );
    try std.testing.expectEqual(object_owner.CollisionResult.Axis.horizontal, result.collided_on);
}

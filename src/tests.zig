const std = @import("std");
const input = @import("input/input.zig");
const direction = @import("input/direction.zig");
const ur = @import("ur.zig");
const vector2d = @import("graphics/vector2d.zig");
const point2d = @import("graphics/point2d.zig");
const sprite_anim = @import("graphics/sprite_anim.zig");
const layer_math = @import("graphics/layer_math.zig");
const object_physics = @import("game/object_physics.zig");
const agm_loader = @import("proto/agm_loader.zig");
const agm_proto = @import("proto/ur.pb.zig");
const map_math = @import("game/map_math.zig");
const object_mod = @import("game/object.zig");
const audio_mod = @import("audio/audio.zig");

test "constants remain stable" {
    try std.testing.expectEqual(@as(i32, 32), ur.tile_width);
    try std.testing.expectEqual(@as(i32, 32), ur.tile_height);
    try std.testing.expectEqual(@as(i32, 640), ur.screen_width);
    try std.testing.expectEqual(@as(i32, 345), ur.screen_height);
}

test "vector2d math and normalization" {
    const a = vector2d.Vector2D.init(3.0, 4.0);
    try std.testing.expectEqual(@as(f64, 5.0), a.length());

    const b = vector2d.Vector2D.init(-1.0, 2.0);
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
    const a = vector2d.Vector2D.init(2.0, 6.0);
    try std.testing.expectEqual(@as(f64, 3.0), a.slope());

    const zero = vector2d.Vector2D.init(0.0, 0.0);
    const normalized = zero.normalize();
    try std.testing.expectEqual(@as(f64, 0.0), normalized.x);
    try std.testing.expectEqual(@as(f64, 0.0), normalized.y);
}

test "point2d operations" {
    const a = point2d.Point2D.init(1.0, 2.0);
    const b = point2d.Point2D.init(3.0, 4.0);
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

test "direction from vector and back" {
    const v1 = vector2d.Vector2D.init(0, -5);
    try std.testing.expectEqual(input.Direction.north, direction.directionFromVector(v1));

    const v2 = vector2d.Vector2D.init(2, 3);
    try std.testing.expectEqual(input.Direction.south_east, direction.directionFromVector(v2));

    const v3 = direction.vectorFromDirection(.north_west);
    try std.testing.expectApproxEqAbs(@as(f64, -0.70710678), v3.x, 0.00001);
    try std.testing.expectApproxEqAbs(@as(f64, -0.70710678), v3.y, 0.00001);
}

test "sprite anim rect uses phase and direction" {
    const rect = sprite_anim.animRect(.east, .walk, 3);
    try std.testing.expectEqual(@as(i32, ur.tile_width * 5 + (ur.tile_width * 3)), rect.x);
    try std.testing.expectEqual(@as(i32, ur.tile_height * 2), rect.y);
    try std.testing.expectEqual(@as(i32, ur.tile_width), rect.w);
    try std.testing.expectEqual(@as(i32, ur.tile_height), rect.h);

    const wait_rect = sprite_anim.animRect(.none, .wait, 0);
    try std.testing.expectEqual(@as(i32, ur.tile_height * 9), wait_rect.y);
}

test "layer math visible range and rects" {
    const screen = layer_math.Rect{ .x = 64, .y = 32, .w = ur.screen_width, .h = ur.screen_height };
    const range = layer_math.visibleRange(screen);
    try std.testing.expectEqual(@as(i32, 2), range.begin_x);
    try std.testing.expectEqual(@as(i32, 1), range.begin_y);

    const src = layer_math.tileSrcRect(3, 2);
    try std.testing.expectEqual(@as(i32, 96), src.x);
    try std.testing.expectEqual(@as(i32, 64), src.y);

    const dst = layer_math.tileDestRect(5, 7);
    try std.testing.expectEqual(@as(i32, 160), dst.x);
    try std.testing.expectEqual(@as(i32, 224), dst.y);
}

test "object physics step from rest" {
    const state = object_physics.MovementState{
        .position = point2d.Point2D.init(10.0, 10.0),
        .velocity = vector2d.Vector2D.init(0, 0),
    };
    const direction_input = vector2d.Vector2D.init(1, 0);
    const next = object_physics.step(state, direction_input);

    try std.testing.expectApproxEqAbs(@as(f64, 0.045), next.velocity.x, 0.000001);
    try std.testing.expectApproxEqAbs(@as(f64, 10.045), next.position.x, 0.000001);
    try std.testing.expectApproxEqAbs(@as(f64, 10.0), next.position.y, 0.000001);
}

test "object physics clamps bounds" {
    const state = object_physics.MovementState{
        .position = point2d.Point2D.init(-1.0, 200.0),
        .velocity = vector2d.Vector2D.init(0.5, -0.5),
    };
    const next = object_physics.step(state, vector2d.Vector2D.init(0, 0));

    try std.testing.expectEqual(@as(f64, 0.0), next.position.x);
    try std.testing.expectEqual(@as(f64, @floatFromInt(ur.map_height - 1)), next.position.y);
    try std.testing.expectEqual(@as(f64, 0.0), next.velocity.x);
    try std.testing.expectEqual(@as(f64, 0.0), next.velocity.y);
}

test "agm loader decodes and converts tile types" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    var agm = agm_proto.AGM{};
    defer agm.deinit(allocator);

    const uuid0 = try allocator.dupe(u8, "t0");
    const title0 = try allocator.dupe(u8, "Tile 0");
    const uuid1 = try allocator.dupe(u8, "t1");
    const title1 = try allocator.dupe(u8, "Tile 1");

    try agm.tileTypes.append(allocator, .{ .uuid = uuid0, .title = title0, .graphicIndex = 4, .solid = true });
    try agm.tileTypes.append(allocator, .{ .uuid = uuid1, .title = title1, .graphicIndex = 2, .solid = false });

    var layer = agm_proto.MapLayer{};
    layer.width = 2;
    layer.height = 2;
    try layer.tiles.append(allocator, 0);
    try layer.tiles.append(allocator, 1);
    try layer.tiles.append(allocator, 1);
    try layer.tiles.append(allocator, 0);
    try agm.layers.append(allocator, layer);

    var writer = std.Io.Writer.Allocating.init(allocator);
    defer writer.deinit();
    try agm.encode(&writer.writer, allocator);

    var decoded = try agm_loader.decodeFromBytes(allocator, writer.written());
    defer decoded.deinit(allocator);

    const tile_types = try agm_loader.tileTypesFromAgm(allocator, &decoded);
    defer allocator.free(tile_types);

    try std.testing.expectEqual(@as(usize, 2), tile_types.len);
    try std.testing.expectEqual(@as(i32, 4), tile_types[0].graphic_index);
    try std.testing.expect(tile_types[0].solid);
    try std.testing.expectEqual(@as(i32, 2), tile_types[1].graphic_index);
    try std.testing.expect(!tile_types[1].solid);
}

test "map math clamps screen rect" {
    const rect = map_math.screenRectForPlayer(0.0, 0.0);
    try std.testing.expectEqual(@as(i32, 0), rect.x);
    try std.testing.expectEqual(@as(i32, 0), rect.y);

    const rect2 = map_math.screenRectForPlayer(1000.0, 1000.0);
    try std.testing.expectEqual(ur.screen_width * 2, rect2.x);
    try std.testing.expectEqual(ur.screen_height * 2, rect2.y);
}

test "object definition parsing" {
    const data = "0\n100\n25\n30\n5\nhello\nworld\nfoo\nbar\n";
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    var def = try object_mod.parseDefinition(allocator, data);
    defer def.deinit(allocator);

    try std.testing.expectEqual(@as(i64, 0), def.gender);
    try std.testing.expectEqual(@as(i64, 100), def.exp);
    try std.testing.expectEqual(@as(i64, 25), def.strength);
    try std.testing.expectEqual(@as(i64, 30), def.constitution);
    try std.testing.expectEqual(@as(i64, 5), def.velmax);
    try std.testing.expectEqual(@as(usize, 2), def.speech.items.len);
    try std.testing.expectEqualStrings("hello", def.speech.items[0].prompt);
    try std.testing.expectEqualStrings("world", def.speech.items[0].response);
    try std.testing.expectEqualStrings("foo", def.speech.items[1].prompt);
    try std.testing.expectEqualStrings("bar", def.speech.items[1].response);
}

test "audio music path joins" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    const path = try audio_mod.musicPath(allocator, "song.mod");
    try std.testing.expectEqualStrings("data/music/song.mod", path);
}

comptime {
    _ = input;
    _ = direction;
    _ = ur;
    _ = vector2d;
    _ = point2d;
    _ = sprite_anim;
    _ = layer_math;
    _ = object_physics;
    _ = agm_loader;
    _ = agm_proto;
    _ = map_math;
    _ = object_mod;
    _ = audio_mod;
}

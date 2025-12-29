const std = @import("std");
const proto = @import("ur.pb.zig");
const layer = @import("../graphics/layer.zig");

pub const AgmData = struct {
    agm: proto.AGM,
    tile_types: []layer.TileType,

    pub fn deinit(self: *AgmData, allocator: std.mem.Allocator) void {
        allocator.free(self.tile_types);
        self.agm.deinit(allocator);
    }
};

pub fn decodeFromBytes(allocator: std.mem.Allocator, bytes: []const u8) !proto.AGM {
    var reader = std.Io.Reader.fixed(bytes);
    return proto.AGM.decode(&reader, allocator);
}

pub fn loadFromFile(allocator: std.mem.Allocator, path: []const u8) !AgmData {
    const data = try std.fs.cwd().readFileAlloc(allocator, path, 10 * 1024 * 1024);
    defer allocator.free(data);

    var agm = try decodeFromBytes(allocator, data);
    errdefer agm.deinit(allocator);

    const tile_types = try tileTypesFromAgm(allocator, &agm);
    return .{ .agm = agm, .tile_types = tile_types };
}

pub fn tileTypesFromAgm(allocator: std.mem.Allocator, agm: *const proto.AGM) ![]layer.TileType {
    const count = agm.tileTypes.items.len;
    const result = try allocator.alloc(layer.TileType, count);

    for (agm.tileTypes.items, 0..) |tile, idx| {
        result[idx] = .{
            .graphic_index = tile.graphicIndex,
            .solid = tile.solid,
        };
    }

    return result;
}

test "agm loader decodes and converts tile types" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    var agm = proto.AGM{};
    defer agm.deinit(allocator);

    const uuid0 = try allocator.dupe(u8, "t0");
    const title0 = try allocator.dupe(u8, "Tile 0");
    const uuid1 = try allocator.dupe(u8, "t1");
    const title1 = try allocator.dupe(u8, "Tile 1");

    try agm.tileTypes.append(allocator, .{ .uuid = uuid0, .title = title0, .graphicIndex = 4, .solid = true });
    try agm.tileTypes.append(allocator, .{ .uuid = uuid1, .title = title1, .graphicIndex = 2, .solid = false });

    var map_layer = proto.MapLayer{};
    map_layer.width = 2;
    map_layer.height = 2;
    try map_layer.tiles.append(allocator, 0);
    try map_layer.tiles.append(allocator, 1);
    try map_layer.tiles.append(allocator, 1);
    try map_layer.tiles.append(allocator, 0);
    try agm.layers.append(allocator, map_layer);

    var writer = std.Io.Writer.Allocating.init(allocator);
    defer writer.deinit();
    try agm.encode(&writer.writer, allocator);

    var decoded = try decodeFromBytes(allocator, writer.written());
    defer decoded.deinit(allocator);

    const tile_types = try tileTypesFromAgm(allocator, &decoded);
    defer allocator.free(tile_types);

    try std.testing.expectEqual(@as(usize, 2), tile_types.len);
    try std.testing.expectEqual(@as(i32, 4), tile_types[0].graphic_index);
    try std.testing.expect(tile_types[0].solid);
    try std.testing.expectEqual(@as(i32, 2), tile_types[1].graphic_index);
    try std.testing.expect(!tile_types[1].solid);
}

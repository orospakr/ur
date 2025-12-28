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

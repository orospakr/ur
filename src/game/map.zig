const std = @import("std");
const SDL = @import("sdl2");
const img = @cImport({
    @cInclude("SDL_image.h");
});

const ur = @import("../ur.zig");
const layer_mod = @import("../graphics/layer.zig");
const map_math = @import("map_math.zig");
const object_mod = @import("object.zig");
const agm_loader = @import("../proto/agm_loader.zig");
const direction = @import("../input/direction.zig");
const input = @import("../input/input.zig");
const cstr = @import("../util/cstr.zig");

pub const Map = struct {
    allocator: std.mem.Allocator,
    map_name: []const u8,
    screen_geom: SDL.SDL_Rect,
    tileset: *SDL.SDL_Texture,
    agm_data: agm_loader.AgmData,
    layers: std.ArrayListUnmanaged(layer_mod.Layer) = .empty,
    objects: std.ArrayListUnmanaged(object_mod.Object) = .empty,
    player_index: usize = 0,

    pub fn init(allocator: std.mem.Allocator, renderer: *SDL.SDL_Renderer, name: []const u8) !Map {
        const name_copy = try allocator.dupe(u8, name);

        const tileset_path = try std.fs.path.join(allocator, &.{ "data", "maps", name, "tiles.png" });
        defer allocator.free(tileset_path);
        const tileset_c = try cstr.addNullByte(allocator, tileset_path);
        defer allocator.free(tileset_c);

        const c_renderer: *img.SDL_Renderer = @ptrCast(renderer);
        const tileset_c_tex = img.IMG_LoadTexture(c_renderer, tileset_c.ptr) orelse return error.TilesetLoadFailed;
        const tileset: *SDL.SDL_Texture = @ptrCast(tileset_c_tex);

        const agm_path = try std.fs.path.join(allocator, &.{ "data", "maps", name, "newformat.agm" });
        defer allocator.free(agm_path);

        var agm_data = try agm_loader.loadFromFile(allocator, agm_path);
        errdefer agm_data.deinit(allocator);

        var map = Map{
            .allocator = allocator,
            .map_name = name_copy,
            .screen_geom = .{ .x = 0, .y = 0, .w = ur.screen_width, .h = ur.screen_height },
            .tileset = tileset,
            .agm_data = agm_data,
        };

        for (agm_data.agm.layers.items) |layer_proto| {
            try map.layers.append(allocator, layer_mod.Layer.init(
                tileset,
                layer_proto.tiles.items,
                agm_data.tile_types,
                layer_proto.width,
                layer_proto.height,
            ));
        }

        return map;
    }

    pub fn deinit(self: *Map) void {
        for (self.objects.items) |*obj| {
            obj.deinit(self.allocator);
        }
        self.objects.deinit(self.allocator);
        for (self.layers.items) |*layer| {
            layer.deinit(self.allocator);
        }
        self.layers.deinit(self.allocator);

        SDL.SDL_DestroyTexture(self.tileset);
        self.agm_data.deinit(self.allocator);
        self.allocator.free(self.map_name);
    }

    pub fn addObject(self: *Map, obj: object_mod.Object) !void {
        try self.objects.append(self.allocator, obj);
        if (self.layers.items.len > 0) {
            const idx = self.objects.items.len - 1;
            try self.layers.items[0].registerObject(self.allocator, &self.objects.items[idx]);
        }
    }

    pub fn setPlayerIndex(self: *Map, index: usize) void {
        self.player_index = index;
    }

    pub fn run(self: *Map, input_dir: input.Direction) void {
        for (self.layers.items) |*layer| {
            layer.advanceAnimation();
        }

        if (self.player_index < self.objects.items.len) {
            const move_vec = direction.vectorFromDirection(input_dir);
            self.objects.items[self.player_index].move(move_vec);
        }

        for (self.objects.items) |*obj| {
            obj.run();
        }

        if (self.player_index < self.objects.items.len) {
            const player = self.objects.items[self.player_index];
            const rect = map_math.screenRectForPlayer(player.position.x, player.position.y);
            self.screen_geom.x = rect.x;
            self.screen_geom.y = rect.y;
        }
    }

    pub fn draw(self: *Map, renderer: *SDL.SDL_Renderer) void {
        for (self.layers.items) |*layer| {
            layer.draw(renderer, self.screen_geom);
        }

        for (self.objects.items) |*obj| {
            obj.draw(renderer, self.screen_geom);
        }
    }
};

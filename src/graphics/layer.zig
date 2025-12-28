const std = @import("std");
const SDL = @import("sdl2");
const ur = @import("../ur.zig");
const layer_math = @import("layer_math.zig");

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
};

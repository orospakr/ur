const std = @import("std");
const SDL = @import("sdl2");
const img = @cImport({
    @cInclude("SDL_image.h");
});

const ur = @import("../ur.zig");
const input = @import("../input/input.zig");
const sprite_anim = @import("sprite_anim.zig");
const cstr = @import("../util/cstr.zig");

pub const Sprite = struct {
    sprite_data: *SDL.SDL_Texture,
    current_dir: input.Direction = .none,
    current_anim: ur.Anim = .walk,
    animation_phase: i64 = 0,
    xpos: i64 = 0,
    ypos: i64 = 0,

    pub fn init(allocator: std.mem.Allocator, renderer: *SDL.SDL_Renderer, filename: []const u8) !Sprite {
        const c_filename = try cstr.addNullByte(allocator, filename);
        defer allocator.free(c_filename);

        const c_renderer: *img.SDL_Renderer = @ptrCast(renderer);
        const texture_c = img.IMG_LoadTexture(c_renderer, c_filename.ptr);
        if (texture_c == null) return error.SpriteLoadFailed;

        const texture: *SDL.SDL_Texture = @ptrCast(texture_c.?);
        return .{ .sprite_data = texture };
    }

    pub fn deinit(self: *Sprite) void {
        SDL.SDL_DestroyTexture(self.sprite_data);
    }

    pub fn advanceAnimation(self: *Sprite) void {
        self.animation_phase = @intCast(SDL.SDL_GetTicks() / 33 / 3 % 8);
    }

    pub fn portraitRect() sprite_anim.Rect {
        return sprite_anim.portraitRect();
    }

    pub fn draw(self: *Sprite, renderer: *SDL.SDL_Renderer, screen_geom: SDL.SDL_Rect) void {
        const anim = sprite_anim.animRect(self.current_dir, self.current_anim, self.animation_phase);

        var src_rect = SDL.SDL_Rect{
            .x = anim.x,
            .y = anim.y,
            .w = anim.w,
            .h = anim.h,
        };

        const dst_x: i32 = @intCast(self.xpos - screen_geom.x);
        const dst_y: i32 = @intCast(self.ypos - screen_geom.y);
        var dst_rect = SDL.SDL_Rect{
            .x = dst_x,
            .y = dst_y,
            .w = ur.tile_width,
            .h = ur.tile_height,
        };

        _ = SDL.SDL_RenderCopy(renderer, self.sprite_data, &src_rect, &dst_rect);
    }
};

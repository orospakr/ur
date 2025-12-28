const std = @import("std");
const SDL = @import("sdl2");
const img = @cImport({
    @cInclude("SDL_image.h");
});

const ur = @import("../ur.zig");
const cstr = @import("../util/cstr.zig");

pub const Font = struct {
    big_font: *SDL.SDL_Texture,
    text_font: *SDL.SDL_Texture,

    pub fn init(allocator: std.mem.Allocator, renderer: *SDL.SDL_Renderer, base_dir: []const u8) !Font {
        const text_path = try std.fs.path.join(allocator, &.{ base_dir, "textfont.png" });
        defer allocator.free(text_path);
        const text_c = try cstr.addNullByte(allocator, text_path);
        defer allocator.free(text_c);

        const text_surface = img.IMG_Load(text_c.ptr);
        if (text_surface == null) return error.TextFontLoadFailed;
        const text_surface_ptr: *SDL.SDL_Surface = @ptrCast(text_surface.?);
        defer SDL.SDL_FreeSurface(text_surface_ptr);

        const fmt_c = text_surface.?.*.format;
        const fmt: *SDL.SDL_PixelFormat = @ptrCast(fmt_c);
        const bpp: i32 = fmt.*.BytesPerPixel;
        const w: i32 = text_surface.?.*.w;
        const h: i32 = text_surface.?.*.h;
        const pixels = @as([*]u8, @ptrCast(text_surface.?.*.pixels));

        var y: i32 = 0;
        while (y < h) : (y += 1) {
            var x: i32 = 0;
            while (x < w * bpp) : (x += bpp) {
                const offset: usize = @intCast(y * text_surface.?.*.pitch + x);
                const pixel_ptr = @as(*u32, @ptrCast(pixels + offset));

                var r: u8 = 0;
                var g: u8 = 0;
                var b: u8 = 0;
                var a: u8 = 0;
                SDL.SDL_GetRGBA(pixel_ptr.*, fmt, &r, &g, &b, &a);

                if (a != 0) {
                    pixel_ptr.* = SDL.SDL_MapRGBA(fmt, 255, 255, 255, 255);
                }
            }
        }

        const text_texture = SDL.SDL_CreateTextureFromSurface(renderer, text_surface_ptr);
        if (text_texture == null) return error.TextTextureCreateFailed;

        const big_path = try std.fs.path.join(allocator, &.{ base_dir, "bigfont.png" });
        defer allocator.free(big_path);
        const big_c = try cstr.addNullByte(allocator, big_path);
        defer allocator.free(big_c);

        const c_renderer: *img.SDL_Renderer = @ptrCast(renderer);
        const big_texture_c = img.IMG_LoadTexture(c_renderer, big_c.ptr);
        if (big_texture_c == null) return error.BigFontLoadFailed;
        const big_texture: *SDL.SDL_Texture = @ptrCast(big_texture_c.?);

        return .{
            .big_font = big_texture.?,
            .text_font = text_texture.?,
        };
    }

    pub fn deinit(self: *Font) void {
        SDL.SDL_DestroyTexture(self.big_font);
        SDL.SDL_DestroyTexture(self.text_font);
    }

    pub fn printText(
        self: *Font,
        renderer: *SDL.SDL_Renderer,
        text: []const u8,
        font_id: ur.FontId,
        dest_pos: SDL.SDL_Point,
        text_color: SDL.SDL_Color,
    ) void {
        const glyph_w: i32 = switch (font_id) {
            .big => ur.font_big_x,
            .text => ur.font_text_x,
        };
        const glyph_h: i32 = switch (font_id) {
            .big => ur.font_big_y,
            .text => ur.font_text_y,
        };
        const texture = switch (font_id) {
            .big => self.big_font,
            .text => self.text_font,
        };

        var i: usize = 0;
        while (i < text.len) : (i += 1) {
            const ascii: i32 = text[i];
            var src_rect = SDL.SDL_Rect{
                .x = (ascii - 1) * glyph_w,
                .y = 0,
                .w = glyph_w,
                .h = glyph_h,
            };

            var dst_rect = SDL.SDL_Rect{
                .x = dest_pos.x + @as(i32, @intCast(i)) * glyph_w,
                .y = dest_pos.y,
                .w = glyph_w,
                .h = glyph_h,
            };

            _ = SDL.SDL_SetTextureColorMod(texture, text_color.r, text_color.g, text_color.b);
            _ = SDL.SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
        }
    }
};

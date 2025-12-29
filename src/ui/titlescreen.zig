const std = @import("std");
const SDL = @import("sdl2");

const ur = @import("../ur.zig");
const font_mod = @import("../graphics/font.zig");
const audio_mod = @import("../audio/audio.zig");
const input = @import("../input/input.zig");
const cstr = @import("../util/cstr.zig");

pub const Titlescreen = struct {
    title_texture: *SDL.SDL_Texture,
    font: *font_mod.Font,
    audio: *audio_mod.Audio,
    scroller_text: []const u8,

    pub fn init(
        allocator: std.mem.Allocator,
        renderer: *SDL.SDL_Renderer,
        base_dir: []const u8,
        font: *font_mod.Font,
        audio: *audio_mod.Audio,
    ) !Titlescreen {
        const text = "                                           Welcome to UR!  Greetz out to Sieg, Thoth, OverDrive!";

        const bmp_path = try std.fs.path.join(allocator, &.{ base_dir, "titlescreen.bmp" });
        defer allocator.free(bmp_path);
        const bmp_c = try cstr.addNullByte(allocator, bmp_path);
        defer allocator.free(bmp_c);

        const surface = SDL.SDL_LoadBMP(bmp_c.ptr) orelse return error.TitleLoadFailed;
        defer SDL.SDL_FreeSurface(surface);

        const texture = SDL.SDL_CreateTextureFromSurface(renderer, surface) orelse return error.TitleTextureFailed;

        try audio.pushBgm("sweetdre.xm");

        return .{
            .title_texture = texture,
            .font = font,
            .audio = audio,
            .scroller_text = text,
        };
    }

    pub fn deinit(self: *Titlescreen) void {
        SDL.SDL_DestroyTexture(self.title_texture);
    }

    pub fn run(self: *Titlescreen, renderer: *SDL.SDL_Renderer, keystate: input.InputState) bool {
        var result = false;

        var title_w: i32 = 0;
        var title_h: i32 = 0;
        _ = SDL.SDL_QueryTexture(self.title_texture, null, null, &title_w, &title_h);

        var logo_rect = SDL.SDL_Rect{
            .x = @divTrunc(ur.screen_width, 2) - @divTrunc(title_w, 2),
            .y = @divTrunc(ur.screen_height, 2) - @divTrunc(title_h, 2),
            .w = title_w,
            .h = title_h,
        };
        _ = SDL.SDL_RenderCopy(renderer, self.title_texture, null, &logo_rect);

        const welcome_text = "Press Start Button!";
        const text_pos = SDL.SDL_Point{
            .x = @divTrunc(ur.screen_width, 2) - @divTrunc(ur.font_text_x * @as(i32, @intCast(welcome_text.len)), 2),
            .y = ur.screen_height - (ur.font_text_y * 2),
        };

        const color = SDL.SDL_Color{ .r = 255, .g = 127, .b = 127, .a = 255 };
        self.font.printText(renderer, welcome_text, .text, text_pos, color);

        const marquee_width = ur.font_text_x * @as(i32, @intCast(self.scroller_text.len)) + ur.screen_width;
        const scroll_x = scrollerOffset(@as(i64, SDL.SDL_GetTicks()), marquee_width);
        const scroller_pos = SDL.SDL_Point{ .x = scroll_x, .y = ur.screen_height - 64 };
        self.font.printText(renderer, self.scroller_text, .text, scroller_pos, color);

        if (keystate.start) {
            self.audio.popBgm();
            result = true;
        }

        return result;
    }
};

pub fn scrollerOffset(ticks: i64, marquee_width: i32) i32 {
    const step = @divTrunc(ticks, 5);
    const width_i64: i64 = marquee_width;
    const offset = @as(i32, @intCast(@mod(step, width_i64)));
    return -offset;
}

test "title scroller offset wraps" {
    const offset = scrollerOffset(0, 100);
    try std.testing.expectEqual(@as(i32, 0), offset);

    const offset2 = scrollerOffset(50, 100);
    try std.testing.expectEqual(@as(i32, -10), offset2);
}

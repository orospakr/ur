const std = @import("std");
const SDL = @import("sdl2");
const img = @cImport({
    @cInclude("SDL_image.h");
});
const ur = @import("ur.zig");
const input = @import("input/input.zig");
const map_mod = @import("game/map.zig");
const object_mod = @import("game/object.zig");
const audio_mod = @import("audio/audio.zig");
const font_mod = @import("graphics/font.zig");
const titlescreen_mod = @import("ui/titlescreen.zig");

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    if (SDL.SDL_Init(SDL.SDL_INIT_VIDEO | SDL.SDL_INIT_EVENTS | SDL.SDL_INIT_AUDIO) < 0) {
        std.log.err("SDL init failed: {s}", .{sdlGetError()});
        return error.SdlInitFailed;
    }
    defer SDL.SDL_Quit();

    if (img.IMG_Init(img.IMG_INIT_PNG) == 0) {
        std.log.err("SDL_image init failed: {s}", .{sdlGetError()});
        return error.SdlImageInitFailed;
    }
    defer img.IMG_Quit();

    const window = SDL.SDL_CreateWindow(
        "Usurper's Retribution",
        SDL.SDL_WINDOWPOS_CENTERED,
        SDL.SDL_WINDOWPOS_CENTERED,
        ur.screen_width,
        ur.screen_height,
        SDL.SDL_WINDOW_SHOWN,
    ) orelse {
        std.log.err("SDL window failed: {s}", .{sdlGetError()});
        return error.SdlWindowFailed;
    };
    defer _ = SDL.SDL_DestroyWindow(window);

    const renderer = SDL.SDL_CreateRenderer(window, -1, SDL.SDL_RENDERER_ACCELERATED) orelse {
        std.log.err("SDL renderer failed: {s}", .{sdlGetError()});
        return error.SdlRendererFailed;
    };
    defer _ = SDL.SDL_DestroyRenderer(renderer);

    var audio = try audio_mod.Audio.init(allocator);
    defer audio.deinit();

    var font = try font_mod.Font.init(allocator, renderer, "data");
    defer font.deinit();

    var title = try titlescreen_mod.Titlescreen.init(allocator, renderer, "data", &font, &audio);
    defer title.deinit();

    var map = try map_mod.Map.init(allocator, renderer, "kv");
    defer map.deinit();

    var player = try object_mod.Object.init(allocator, renderer, "data/objs", "al");
    player.faction = .ff;
    player.obj_type = .player;
    player.position = .{ .x = 13, .y = 9 };
    try map.addObject(player);
    map.setPlayerIndex(0);

    var mickey = try object_mod.Object.init(allocator, renderer, "data/objs", "mickey");
    mickey.faction = .bad_nik;
    mickey.position = .{ .x = 12, .y = 13 };
    try map.addObject(mickey);

    var input_state = input.InputState{};
    var run_state: ur.RunState = .title_screen;
    var game_music_started = false;

    var running = true;
    while (running) {
        var ev: SDL.SDL_Event = undefined;
        while (SDL.SDL_PollEvent(&ev) != 0) {
            switch (ev.type) {
                SDL.SDL_QUIT => running = false,
                SDL.SDL_KEYDOWN => handleKeyEvent(&input_state, ev.key.keysym.sym, true),
                SDL.SDL_KEYUP => handleKeyEvent(&input_state, ev.key.keysym.sym, false),
                else => {},
            }
        }

        _ = SDL.SDL_SetRenderDrawColor(renderer, 0x20, 0x1F, 0x1B, 0xFF);
        _ = SDL.SDL_RenderClear(renderer);

        if (run_state == .title_screen) {
            if (title.run(renderer, input_state)) {
                run_state = .in_game;
            }
        } else {
            const move_dir = input.directionFromInput(input_state);
            map.run(move_dir);
            map.draw(renderer);
        }

        if (run_state == .in_game and !game_music_started) {
            try audio.pushBgm("7thheaven.mod");
            game_music_started = true;
        }

        audio.update();
        SDL.SDL_RenderPresent(renderer);
    }
}

fn handleKeyEvent(state: *input.InputState, key: SDL.SDL_Keycode, down: bool) void {
    switch (key) {
        SDL.SDLK_LEFT => state.left = down,
        SDL.SDLK_RIGHT => state.right = down,
        SDL.SDLK_UP => state.up = down,
        SDL.SDLK_DOWN => state.down = down,
        SDL.SDLK_RETURN => state.start = down,
        SDL.SDLK_SPACE => state.action = down,
        SDL.SDLK_RCTRL => state.select = down,
        else => {},
    }
}

fn sdlGetError() []const u8 {
    const err_ptr: [*:0]const u8 = SDL.SDL_GetError();
    return std.mem.sliceTo(err_ptr, 0);
}

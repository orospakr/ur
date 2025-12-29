const std = @import("std");
const SDL = @import("sdl2");

const c_openmpt = @cImport({
    @cInclude("libopenmpt/libopenmpt.h");
});

pub const Audio = struct {
    allocator: std.mem.Allocator,
    obtained_spec: SDL.SDL_AudioSpec = undefined,
    mix_buffer: []i16 = &.{},
    device_id: SDL.SDL_AudioDeviceID = 0,
    bytes_per_buffer: usize = 0,
    modules: std.StringHashMapUnmanaged(*c_openmpt.openmpt_module) = .empty,
    bgm_stack: std.ArrayListUnmanaged([]const u8) = .empty,
    current_module: ?*c_openmpt.openmpt_module = null,

    pub fn init(allocator: std.mem.Allocator) !Audio {
        var audio = Audio{ .allocator = allocator };

        try audio.loadDefaultModules();
        try audio.openDevice();

        return audio;
    }

    pub fn deinit(self: *Audio) void {
        self.current_module = null;
        if (self.device_id != 0) {
            SDL.SDL_ClearQueuedAudio(self.device_id);
            SDL.SDL_CloseAudioDevice(self.device_id);
        }

        if (self.mix_buffer.len > 0) {
            self.allocator.free(self.mix_buffer);
        }

        var it = self.modules.iterator();
        while (it.next()) |entry| {
            c_openmpt.openmpt_module_destroy(entry.value_ptr.*);
            self.allocator.free(entry.key_ptr.*);
        }
        self.modules.deinit(self.allocator);

        for (self.bgm_stack.items) |name| {
            self.allocator.free(name);
        }
        self.bgm_stack.deinit(self.allocator);
    }

    pub fn pushBgm(self: *Audio, name: []const u8) !void {
        const owned = try self.allocator.dupe(u8, name);
        try self.bgm_stack.append(self.allocator, owned);
        self.changeMusic(owned);
    }

    pub fn popBgm(self: *Audio) void {
        if (self.bgm_stack.items.len == 0) return;

        if (self.bgm_stack.pop()) |last| {
            self.allocator.free(last);
        }

        if (self.bgm_stack.items.len == 0) {
            self.current_module = null;
            return;
        }

        const name = self.bgm_stack.items[self.bgm_stack.items.len - 1];
        self.changeMusic(name);
    }

    pub fn changeMusic(self: *Audio, name: []const u8) void {
        if (self.modules.get(name)) |module| {
            self.current_module = module;
        } else {
            std.log.warn("audio: module not found: {s}", .{name});
        }
    }

    fn openDevice(self: *Audio) !void {
        var desired = SDL.SDL_AudioSpec{
            .freq = 44100,
            .format = SDL.AUDIO_S16LSB,
            .channels = 2,
            .silence = 0,
            .samples = 512,
            .padding = 0,
            .size = 0,
            .callback = null,
            .userdata = null,
        };

        var obtained: SDL.SDL_AudioSpec = undefined;
        const device = SDL.SDL_OpenAudioDevice(null, 0, &desired, &obtained, 0);
        if (device == 0) return error.AudioOpenFailed;

        self.obtained_spec = obtained;
        self.device_id = device;

        const buffer_samples = @as(usize, @intCast(obtained.samples)) * @as(usize, obtained.channels);
        if (buffer_samples > 0) {
            self.mix_buffer = try self.allocator.alloc(i16, buffer_samples);
            self.bytes_per_buffer = buffer_samples * @sizeOf(i16);
        }

        SDL.SDL_PauseAudioDevice(device, 0);
    }

    fn loadDefaultModules(self: *Audio) !void {
        const module_names = [_][]const u8{ "sweetdre.xm", "7thheaven.mod" };
        for (module_names) |name| {
            self.loadMusic(name) catch |err| {
                std.log.warn("audio: failed to load {s}: {s}", .{ name, @errorName(err) });
            };
        }
    }

    fn loadMusic(self: *Audio, name: []const u8) !void {
        const path = try musicPath(self.allocator, name);
        defer self.allocator.free(path);

        const data = try std.fs.cwd().readFileAlloc(self.allocator, path, 16 * 1024 * 1024);
        defer self.allocator.free(data);

        var error_code: c_int = 0;
        const module = c_openmpt.openmpt_module_create_from_memory2(
            data.ptr,
            data.len,
            null,
            null,
            null,
            null,
            &error_code,
            null,
            null,
        );

        if (module == null) {
            std.log.warn("audio: openmpt error {d}", .{error_code});
            return error.ModuleLoadFailed;
        }

        const key = try self.allocator.dupe(u8, name);
        try self.modules.put(self.allocator, key, module.?);
    }

    pub fn update(self: *Audio) void {
        if (self.device_id == 0) return;
        if (self.current_module == null) return;
        if (self.mix_buffer.len == 0) return;

        const queued = SDL.SDL_GetQueuedAudioSize(self.device_id);
        if (queued > self.bytes_per_buffer * 2) return;

        const frames = self.mix_buffer.len / 2;
        const read_frames = c_openmpt.openmpt_module_read_interleaved_stereo(
            self.current_module.?,
            44100,
            frames,
            self.mix_buffer.ptr,
        );
        if (read_frames == 0) return;

        const samples = read_frames * 2;
        const bytes = samples * @sizeOf(i16);
        _ = SDL.SDL_QueueAudio(self.device_id, self.mix_buffer.ptr, @intCast(bytes));
    }
};

pub fn musicPath(allocator: std.mem.Allocator, name: []const u8) ![]const u8 {
    return std.fs.path.join(allocator, &.{ "data", "music", name });
}

test "audio music path joins" {
    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();
    const allocator = arena.allocator();

    const path = try musicPath(allocator, "song.mod");
    try std.testing.expectEqualStrings("data/music/song.mod", path);
}

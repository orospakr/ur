const std = @import("std");
const SDL = @import("sdl2");

const ur = @import("../ur.zig");
const sprite_mod = @import("../graphics/sprite.zig");
const vector2d = @import("../graphics/vector2d.zig");
const point2d = @import("../graphics/point2d.zig");
const direction = @import("../input/direction.zig");
const object_physics = @import("object_physics.zig");

pub const Definition = struct {
    gender: i64,
    exp: i64,
    strength: i64,
    constitution: i64,
    velmax: i64,
    speech: std.ArrayListUnmanaged(ur.TalkData) = .empty,

    pub fn deinit(self: *Definition, allocator: std.mem.Allocator) void {
        for (self.speech.items) |entry| {
            allocator.free(entry.prompt);
            allocator.free(entry.response);
        }
        self.speech.deinit(allocator);
    }
};

fn parseI64(line: []const u8) !i64 {
    return std.fmt.parseInt(i64, trimLine(line), 10);
}

fn trimLine(line: []const u8) []const u8 {
    return std.mem.trimRight(u8, line, "\r");
}

fn nextLine(iter: *std.mem.SplitIterator(u8, .scalar)) []const u8 {
    return iter.next() orelse "";
}

pub const Object = struct {
    sprite: sprite_mod.Sprite,
    position: point2d.Point2D = .{ .x = 0, .y = 0 },
    velocity: vector2d.Vector2D = .{ .x = 0, .y = 0 },
    direction_input: vector2d.Vector2D = .{ .x = 0, .y = 0 },
    area_influence: ur.Influence = .{ .x = 0, .y = 0, .h = ur.tile_height, .w = ur.tile_width },
    name: []const u8,
    speech: std.ArrayListUnmanaged(ur.TalkData) = .empty,

    exp: i64 = 0,
    strength: i64 = 0,
    constitution: i64 = 0,
    gender: i64 = 0,
    velmax: i64 = 0,

    dead: bool = false,
    obj_type: ur.ObjType = .inanimate,
    faction: ur.Faction = .bad_nik,

    pub fn init(
        allocator: std.mem.Allocator,
        renderer: *SDL.SDL_Renderer,
        object_path: []const u8,
        object_name: []const u8,
    ) !Object {
        const name_copy = try allocator.dupe(u8, object_name);

        const sprite_path = try std.fs.path.join(allocator, &.{ object_path, object_name, "sprites.png" });
        defer allocator.free(sprite_path);

        const sprite = try sprite_mod.Sprite.init(allocator, renderer, sprite_path);

        var obj = Object{ .sprite = sprite, .name = name_copy };
        try obj.loadDefinition(allocator, object_path, object_name);
        obj.updateInfluence();

        return obj;
    }

    pub fn deinit(self: *Object, allocator: std.mem.Allocator) void {
        for (self.speech.items) |entry| {
            allocator.free(entry.prompt);
            allocator.free(entry.response);
        }
        self.speech.deinit(allocator);
        allocator.free(self.name);
        self.sprite.deinit();
    }

    pub fn move(self: *Object, input_vec: vector2d.Vector2D) void {
        self.direction_input = input_vec;
        self.sprite.current_dir = direction.directionFromVector(input_vec);
    }

    pub fn run(self: *Object) void {
        if (self.dead) {
            self.velocity = vector2d.Vector2D.init(0, 0);
            return;
        }

        const next = object_physics.step(.{ .position = self.position, .velocity = self.velocity }, self.direction_input);
        self.position = next.position;
        self.velocity = next.velocity;

        self.sprite.current_anim = .walk;
        self.sprite.xpos = @intFromFloat(self.position.x * @as(f64, @floatFromInt(ur.tile_width)));
        self.sprite.ypos = @intFromFloat(self.position.y * @as(f64, @floatFromInt(ur.tile_height)));
        self.sprite.advanceAnimation();

        self.updateInfluence();
    }

    pub fn draw(self: *Object, renderer: *SDL.SDL_Renderer, screen_geom: SDL.SDL_Rect) void {
        self.sprite.draw(renderer, screen_geom);
    }

    fn updateInfluence(self: *Object) void {
        self.area_influence.w = ur.tile_width;
        self.area_influence.h = ur.tile_height;
        self.area_influence.x = @intFromFloat(self.position.x * @as(f64, @floatFromInt(ur.tile_width)));
        self.area_influence.y = @intFromFloat(self.position.y * @as(f64, @floatFromInt(ur.tile_height)));

        if (self.dead) {
            self.area_influence.x = 0;
            self.area_influence.y = 0;
            self.area_influence.w = 0;
            self.area_influence.h = 0;
        }
    }

    fn loadDefinition(self: *Object, allocator: std.mem.Allocator, object_path: []const u8, object_name: []const u8) !void {
        const def_path = try std.fs.path.join(allocator, &.{ object_path, object_name, "def.txt" });
        defer allocator.free(def_path);

        const data = try std.fs.cwd().readFileAlloc(allocator, def_path, 64 * 1024);
        defer allocator.free(data);

        var parsed = try parseDefinition(allocator, data);
        defer parsed.deinit(allocator);

        self.gender = parsed.gender;
        self.exp = parsed.exp;
        self.strength = parsed.strength;
        self.constitution = parsed.constitution;
        self.velmax = parsed.velmax;

        for (parsed.speech.items) |entry| {
            const prompt = try allocator.dupe(u8, entry.prompt);
            const response = try allocator.dupe(u8, entry.response);
            try self.speech.append(allocator, .{ .prompt = prompt, .response = response });
        }
    }

};

pub fn parseDefinition(allocator: std.mem.Allocator, data: []const u8) !Definition {
    var iter = std.mem.splitScalar(u8, data, '\n');

    var def = Definition{
        .gender = try parseI64(nextLine(&iter)),
        .exp = try parseI64(nextLine(&iter)),
        .strength = try parseI64(nextLine(&iter)),
        .constitution = try parseI64(nextLine(&iter)),
        .velmax = 0,
    };
    errdefer def.deinit(allocator);

    var first_prompt: ?[]const u8 = null;
    const vel_line = nextLine(&iter);
    if (vel_line.len > 0) {
        def.velmax = std.fmt.parseInt(i64, trimLine(vel_line), 10) catch blk: {
            first_prompt = vel_line;
            break :blk 0;
        };
    }

    if (first_prompt) |prompt_line| {
        const response_line = iter.next() orelse "";
        const prompt = try allocator.dupe(u8, trimLine(prompt_line));
        const response = try allocator.dupe(u8, trimLine(response_line));
        try def.speech.append(allocator, .{ .prompt = prompt, .response = response });
    }

    while (iter.next()) |prompt_line| {
        const response_line = iter.next() orelse break;
        const prompt = try allocator.dupe(u8, trimLine(prompt_line));
        const response = try allocator.dupe(u8, trimLine(response_line));
        try def.speech.append(allocator, .{ .prompt = prompt, .response = response });
    }

    return def;
}

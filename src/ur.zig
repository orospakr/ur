pub const revision_major: i32 = 0;
pub const revision_minor: i32 = 1;
pub const revision_micro: i32 = 0;
pub const revision_edition = "20th Anniversary Edition";

pub const tile_width: i32 = 32;
pub const tile_height: i32 = 32;

pub const map_height: i32 = 100;
pub const map_width: i32 = 100;

pub const screen_width: i32 = 640;
pub const screen_height: i32 = 345;

pub const max_objects: i32 = 1000;

pub const font_big_x: i32 = 32;
pub const font_big_y: i32 = 32;
pub const font_text_x: i32 = 16;
pub const font_text_y: i32 = 18;

pub const RunState = enum {
    quit,
    in_game,
    title_screen,
};

pub const FontId = enum {
    big,
    text,
};

pub const Influence = struct {
    x: i64,
    y: i64,
    h: i64,
    w: i64,
};

pub const TalkData = struct {
    prompt: []const u8,
    response: []const u8,
};

pub const Anim = enum {
    walk,
    run,
    wait,
    flail,
    yawn,
};

pub const ObjType = enum {
    player,
    inanimate,
};

pub const Faction = enum {
    ff,
    bad_nik,
};

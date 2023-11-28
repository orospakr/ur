#ifndef UR_H_
#define UR_H_

#include <SDL.h>
#include <string>

namespace ur {

#define REVISION_MAJOR 0
#define REVISION_MINOR 1
#define REVISION_MICRO 0

#define REVISION_EDITION "20th Anniversary Edition"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define MAP_HEIGHT 100
#define MAP_WIDTH 100

// aspect ratio is academy flat to fit on a 640x480 screen
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 345

// maximum number of objects
#define MAX_OBJS 1000

#define FONT_BIG_X 32
#define FONT_BIG_Y 32
#define FONT_TEXT_X 16
#define FONT_TEXT_Y 18

enum UR_RUN_STATE {
    urGameState_Quit,
    urGameState_InGame,
    urGameState_TitleScreen
};

enum UR_FONT_ENUM { urFont_Big, urFont_Text };

struct UR_INFLUENCE {
    Sint64 x;
    Sint64 y;
    Sint64 h;
    Sint64 w;
};

struct UR_INPUT {
    bool up;
    bool down;
    bool left;
    bool right;
    bool start;
    bool select;
    bool action;
    bool cancel;
} const UR_INPUT_DEFAULT = {false, false, false, false,
                            false, false, false, false};

enum UR_KEYPAD_ENUM {
    urKP_Left,
    urKP_Right,
    urKP_Up,
    urKP_Down,
    urKP_Start,
    urKP_Select,
    urKP_Action,
    urKP_Cancel,
    urKP_None
};

enum UR_ANIM_ENUM {
    urAnimWalk,
    urAnimRun,
    urAnimWait,
    urAnimFlail,
    urAnimYawn
};

enum UR_DIRECTION_ENUM {
    urDirNorth,
    urDirSouth,
    urDirEast,
    urDirWest,
    urDirNorthEast,
    urDirNorthWest,
    urDirSouthEast,
    urDirSouthWest,
    urDirNone
};

struct UR_TALK_DATA {
    std::string prompt;
    std::string response;
};

enum UR_OBJTYPE_ENUM { urObj_Player, urObj_Inanimate };

enum UR_FACTION_ENUM { urFact_FF, urFact_BadNik };

} // namespace ur

#endif // UR_H_

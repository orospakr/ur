#define REVISION_MAJOR 0
#define REVISION_MINOR 0
#define REVISION_MICRO 1

#define REVISION_EDITION "Technology Preview 1"


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

// structure definitions
#ifndef UR_H
#define UR_H

enum UR_FONT_ENUM
{
  urFont_Big,
  urFont_Text
};

struct UR_INFLUENCE
{
  Sint64 x;
  Sint64 y;
  Sint64 h;
  Sint64 w;
};

enum UR_KEYPAD_ENUM
{
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

enum UR_ANIM_ENUM
{
  urAnimWalk,
  urAnimRun,
  urAnimWait,
  urAnimFlail,
  urAnimYawn
};

enum UR_DIRECTION_ENUM
{
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

struct UR_TALK_DATA
{
  std::string prompt;
  std::string response;
};

enum UR_OBJTYPE_ENUM
{
  urObj_Player,
  urObj_Inanimate
};

enum UR_FACTION_ENUM
{
  urFact_FF,
  urFact_BadNik
};

#endif // UR_H

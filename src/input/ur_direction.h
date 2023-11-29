//
// Created by Andrew Clunis on 2023-11-28.
//

#ifndef UR_UR_DIRECTION_H
#define UR_UR_DIRECTION_H

#include "graphics/Vector2D.h"

namespace ur {
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

/**
 * Returns the direction value best representing the given vector.
  */
[[nodiscard]] UR_DIRECTION_ENUM directionFromVector(Vector2D vector);

/**
 * Returns a Vector2D describing the given direction value.
 */
[[nodiscard]] Vector2D vectorFromDirection(UR_DIRECTION_ENUM direction);

} // namespace ur

#endif // UR_UR_DIRECTION_H

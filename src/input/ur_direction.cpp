//
// Created by Andrew Clunis on 2023-11-28.
//

#include "ur_direction.h"
#include "graphics/Vector2D.h"

namespace ur {
    UR_DIRECTION_ENUM directionFromVector(Vector2D vector) {
        if (vector.x == 0 && vector.y == 0) {
            return urDirNone;
        }

        if (vector.x == 0) {
            if (vector.y > 0) {
                return urDirSouth;
            } else {
                return urDirNorth;
            }
        }

        if (vector.y == 0) {
            if (vector.x > 0) {
                return urDirEast;
            } else {
                return urDirWest;
            }
        }

        if (vector.x > 0) {
            if (vector.y > 0) {
                return urDirSouthEast;
            } else {
                return urDirNorthEast;
            }
        } else {
            if (vector.y > 0) {
                return urDirSouthWest;
            } else {
                return urDirNorthWest;
            }
        }
    }

    Vector2D vectorFromDirection(UR_DIRECTION_ENUM direction) {
        // being sure to normalize the diagonal vectors.
        switch (direction) {
            case urDirNorth:
                return Vector2D(0, -1);
            case urDirSouth:
                return Vector2D(0, 1);
            case urDirEast:
                return Vector2D(1, 0);
            case urDirWest:
                return Vector2D(-1, 0);
            case urDirNorthEast:
                return Vector2D(1, -1).normalize();
            case urDirNorthWest:
                return Vector2D(-1, -1).normalize();
            case urDirSouthEast:
                return Vector2D(1, 1).normalize();
            case urDirSouthWest:
                return Vector2D(-1, 1).normalize();
            case urDirNone:
                return Vector2D(0, 0);
        }
    }
} // namespace ur
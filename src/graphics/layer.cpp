/*
    This file is part of Usurper's Retribution.

    Usurper's Retribution is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Usurper's Retribution is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Usurper's Retribution; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "graphics/layer.h" // class's header file
#include "agm.pb.h"
#include "layer.h"
#include <memory>

#include "Point2D.h"
#include "Vector2D.h"

namespace ur {

// class constructor
Layer::Layer(const MapLayer *mapLayer, const std::shared_ptr<AGM> agm,
             int layerIndex, SDL_Texture *tileset, SDL_Renderer *renderer)
    : tilepile(tileset), tilesAnimPos(0), layerIndex(layerIndex),
      floorGraphicalMap(), mapLayer(mapLayer), agm(agm) {
    // populate floorGraphicalMap
    for (int ycounter = 0; ycounter < MAP_HEIGHT; ycounter++) {
        for (int xcounter = 0; xcounter < MAP_WIDTH; xcounter++) {
            floorGraphicalMap[xcounter][ycounter] =
                mapLayer->tiles(xcounter + (ycounter * MAP_WIDTH));
        }
    }
}

// class destructor
Layer::~Layer() = default;

Sint64 Layer::drawToScreen(SDL_Renderer *renderer, SDL_Rect screenGeom) {
    Sint64 beginY = screenGeom.y / 32;
    Sint64 endY = beginY + (SCREEN_HEIGHT / 32);
    Sint64 beginX = screenGeom.x / 32;
    Sint64 endX = beginX + (SCREEN_WIDTH / 32);

    endX += 2; // these two are there just so it overlaps and there's no
    // blockiness at the right and bottom edges
    endY += 2;

    // std::cout << screenGeom.w/32 << std::endl << screenGeom.h/32 << std::endl
    // << std::endl;
    for (Sint64 ycounter = beginY; ycounter < endY; ycounter++) {
        for (Sint64 xcounter = beginX; xcounter < endX; xcounter++) {
            SDL_Rect *srcRect;
            SDL_Rect *dstRect;
            srcRect = getTileSrcCoord(floorGraphicalMap[xcounter][ycounter]);
            dstRect = getTileDestCoord(xcounter, ycounter);
            // std::cout << "The requested tilepile blit's source coordinates
            // and dimensions are: "; std::cout << " X origin: " << srcRect->x
            // << " Y origin: " << srcRect->y << " Height: " << srcRect->h << "
            // Width: " << srcRect->w << std::endl; std::cout << "The requested
            // renderer destination coordinates and dimensions are: "; std::cout
            // << " X origin: " << dstRect->x << " Y origin: " << dstRect->y <<
            // " Height: " << dstRect->h << " Width: " << dstRect->w <<
            // std::endl;
            dstRect->x -= screenGeom.x;
            dstRect->y -= screenGeom.y;
            SDL_RenderCopy(renderer, tilepile, srcRect, dstRect);
            delete srcRect;
            delete dstRect;
        }
    }

    // draw all objects:
    for (auto object : this->registeredObjects) {
        object->drawToScreen(renderer, screenGeom);
    }

    return 0;
}

SDL_Rect *Layer::getTileSrcCoord(Sint64 number) {
    auto tileType = this->agm->tiletypes()[number];

    SDL_Rect *result = new SDL_Rect;
    result->h = TILE_HEIGHT;
    result->w = TILE_WIDTH;
    result->x = TILE_WIDTH * (tileType.graphicindex());
    result->y = TILE_HEIGHT * tilesAnimPos;
    return result;
}

SDL_Rect *Layer::getTileDestCoord(Sint64 x, Sint64 y) {
    SDL_Rect *result = new SDL_Rect;
    result->h = TILE_HEIGHT;
    result->w = TILE_WIDTH;
    result->x = TILE_WIDTH * x;
    result->y = TILE_HEIGHT * y;
    return result;
}

void Layer::quickAGMPrint() {
    for (Sint64 ycounter = 0; ycounter < MAP_HEIGHT; ycounter++) {
        for (Sint64 xcounter = 0; xcounter < MAP_WIDTH; xcounter++) {
            std::cout << floorGraphicalMap[xcounter][ycounter];
        }
        std::cout << "\n";
    }
}

Sint64 Layer::run() {
    tilesAnimPos = SDL_GetTicks() / 33 / 3 % 8;

    for (Sint64 counter = 0; counter < this->registeredObjects.size();
         counter++) {
        this->registeredObjects[counter]->run();
    }

    return 0;
}

void Layer::registerObject(Object *obj) { registeredObjects.push_back(obj); }

// Physics:

ObjectOwner::CollisionResult
Layer::checkMapPathCollision(Object *obj, Point2D position, Vector2D vector) {
    // TODO stub, for now.
    return ObjectOwner::CollisionResult{ObjectOwner::CollisionResult::None,
                                        vector, 0, nullptr};

    // step 0: make mutable copy of vector.
    // step 1: use an epsilon value to iterate along the mutable vector until we
    // hit a solid tile. If we hit a solid tile, determine which edge mutate
    // local vector to clamp to that edge. be aware that mutated vector may
    // cause iteration issues, because length/magnitude will change.  Consider a
    // do/while in lieu of for(). step 2: if no hits, return original vector
    // with no changes.
}
//
//    ObjectOwner::CollisionResult
//    Layer::checkMapPathCollisionOLD(Object *obj, Sint64 xpos, Sint64 ypos,
//    Sint64 xvel,
//                                    Sint64 yvel) {
//
//        if (xvel == 0 && yvel == 0) {
//            return ObjectOwner::CollisionResult{false, 0, 0, 0, nullptr};
//        }
//
//
//        Vector2D velocity(
//                static_cast<float>(xvel) / TILE_WIDTH,
//                static_cast<float>(yvel) / TILE_HEIGHT
//        );
//
//        Point2D position(
//                static_cast<float>(xpos) / TILE_WIDTH,
//                static_cast<float>(ypos) / TILE_HEIGHT
//        );
//
//        std::cout << "Checking for collision at position: " << xpos << ", " <<
//        ypos << ", " << position << std::endl;
//
//
//        std::cout << "Velocity: " << xvel << ", " << yvel << ", " << velocity
//        << std::endl;
//
//        // iterate by a small epsilon size to search for a tile to count as
//        edge. Fudge (epsilon) factor 10% of tile width.
//
//
//        float epsilon = 0.02f;
//
//        for (double i = 0; i < velocity.length(); i += epsilon) {
//            Vector2D velocityStep = i == 0 ? Vector2D() : velocity / i;
//            Point2D testPoint = position + (velocityStep * i);
//
//            Sint64 testPointX = static_cast<Sint64>(testPoint.x);
//            Sint64 testPointY = static_cast<Sint64>(testPoint.y);
//            std::cout << "  Testing point: " << testPointX << ", " <<
//            testPointY << ", " << testPoint << std::endl;
//
//            Sint64 futureBlock =
//            this->floorGraphicalMap[testPointX][testPointY];
//
//            // TODO: CollisionResult should identify axis of collision, not
//            assume both.
//
//            // OK, new problem.  If we want to conserve momentum on the
//            non-colliding axis, then this iterative
//            // approach has a problem, because if we bail out at first
//            collision time, the non-colliding axis'
//            // velocity could overrun its upcoming collision point.  So we
//            need to keep iterating, with the clamped
//            // vector, until we hit the next collision point.
//
//            // It seems like the interface of checkMapPathCollision() needs to
//            change to be a transform
//            // on a vector (with possibly hint flags to object can react with
//            behaviour/sound effects.)
//
//            auto tileType =
//            this->agm->tiletypes()[static_cast<int>(futureBlock)]; if
//            (tileType.solid()) {
//                // step 1: determine which edge of the tile we collided with.
//
//                // step 2: identify collision point on that edge, and return
//                it.
//
//
//
//
//
//                Sint64 collisionX, collisionY;
//                // Depending on the orientation of the vector, return the
//                appropriate *edge* of the tile: if (velocityStep.x > 0) {
//                    collisionX = static_cast<Sint64>((testPoint.x *
//                    TILE_WIDTH) - TILE_WIDTH);
//                } else if (velocityStep.x < 0) {
//                    collisionX = static_cast<Sint64>((testPoint.x *
//                    TILE_WIDTH) + TILE_WIDTH);
//                } else {
//                    collisionX = static_cast<Sint64>((testPoint.x *
//                    TILE_WIDTH));
//                }
//
//                if (velocityStep.y > 0) {
//                    collisionY = static_cast<Sint64>((testPoint.y *
//                    TILE_HEIGHT) - TILE_HEIGHT);
//                } else if (velocityStep.y < 0) {
//                    collisionY = static_cast<Sint64>((testPoint.y *
//                    TILE_HEIGHT) + TILE_HEIGHT);
//                } else {
//                    collisionY = static_cast<Sint64>((testPoint.y *
//                    TILE_HEIGHT));
//                }
//
//
//
//
////                Sint64 collisionX = static_cast<Sint64>((previousTestPoint.x
///* TILE_WIDTH)); /                Sint64 collisionY =
/// static_cast<Sint64>((previousTestPoint.y * TILE_HEIGHT));
//                std::cout << "    Collision detected at point: " << collisionX
//                << ", " << collisionY << ", "
//                          << testPoint << std::endl;
//                return ObjectOwner::CollisionResult{true, collisionX,
//                collisionY,
//                                                    futureBlock, &tileType};
//            }
//        }
//
//        std::cout << "    No collision detected." << std::endl;
//        return ObjectOwner::CollisionResult{false, 0, 0, 0, nullptr};
//
//        // TODO: the limitation with this approach is that it only checks
//        destination tile,
//        // not the path. so if velocity is too high, you'll glitch through
//        walls. Also, character stops early
//        // if velocity tile check hits solid tile, even if gap remains.
//
//        // Resolve this by searching along the vector for the first tile that
//        is solid, and then clamping velocity
//        // to the edge of that tile.
//
//
//        // search along tile width along vector until we hit first solid tile.
//        First, we need to determine
//        // the slope of the vector so we can determine how much displacement
//        is required to evenly hit the same
//        // spot on each tile each iteration.
//
//
//
//
//
//
//
//
//
//
//        // old implementation that does not do proper edge detection:
//        Sint64 futureX =
//                xpos + xvel; // values that could be... but only if the APM
//                permits it!
//        Sint64 futureY = ypos + yvel;
//        int futureBlock;
//        futureBlock = this->floorGraphicalMap[(futureX + 15) / TILE_WIDTH]
//        [(futureY + 25) / TILE_HEIGHT];
//
//        auto tiletypes = this->agm->tiletypes();
//
//        auto tileType = this->agm->tiletypes()[futureBlock];
//
//        if (tileType.solid()) {
//            return ObjectOwner::CollisionResult{true, futureX, futureY,
//            futureBlock, &tileType};
//        } else {
//            return ObjectOwner::CollisionResult{false, 0, 0, 0, nullptr};
//        }
//    }
} // namespace ur

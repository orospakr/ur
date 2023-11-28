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
        for (auto object: this->registeredObjects) {
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
    Layer::checkMapPathCollision(Object *obj, Point2D position, Vector2D velocity) {
        const float epsilon = 0.02f;

        ObjectOwner::CollisionResult::Axis collidedOn = ObjectOwner::CollisionResult::Axis::None;
        // if collidedOn is Axis::Horizontal, then a collision has occurred along the vector, and we should clamp
        // the velocity along the X axis.  The clamp value is in absolute terms, in the layer's coordinate space.

        // Same for Axis::Vertical and Y axis.
        double collisionClampX = 0;
        double collisionClampY = 0;

        // here's how you turn on the bit:
        //        collidedOn = static_cast<ObjectOwner::CollisionResult::Axis>(collidedOn | ObjectOwner::CollisionResult::Axis::Horizontal);

        for (double i = 0; i < velocity.length(); i += epsilon) {
            // step 0. apply collidedOn clamp to velocity.


            Vector2D velocityStep = i == 0 ? Vector2D() : velocity / i;
            Point2D testPointUnclamped = position + (velocityStep * i);
            Point2D testPoint;
            if (collidedOn == ObjectOwner::CollisionResult::Axis::Horizontal) {
                testPoint = Point2D(testPointUnclamped.x, position.y);
            } else if (collidedOn == ObjectOwner::CollisionResult::Axis::Vertical) {
                testPoint = Point2D(position.x, testPointUnclamped.y);
            } else {
                testPoint = testPointUnclamped;
            }

            auto testPointX = static_cast<Sint64>(testPoint.x);
            auto testPointY = static_cast<Sint64>(testPoint.y);
            std::cout << "  Testing point: " << testPointX << ", " <<
                      testPointY << ", " << testPoint << std::endl;

            Sint64 futureBlock = this->floorGraphicalMap[testPointX][testPointY];

            // OK, new problem.  If we want to conserve momentum on the non-colliding axis, then this iterative
            // approach has a problem, because if we bail out at first collision time, the non-colliding axis'
            // velocity could overrun its upcoming collision point.  So we need to keep iterating, with the clamped
            // vector, until we hit the next collision point.

            // It seems like the interface of checkMapPathCollision() needs to change to be a transform
            // on a vector (with possibly hint flags to object can react with behaviour/sound effects.)

            auto tileType = this->agm->tiletypes()[static_cast<int>(futureBlock)];
            if (tileType.solid()) {
                // step 1: determine which edge of the tile we collided with.
                Sint64 collisionX = 0;
                Sint64 collisionY = 0;
                if (velocity.x > 0) {
                    collisionX = testPointX * TILE_WIDTH;
                } else if (velocity.x < 0) {
                    collisionX = (testPointX + 1) * TILE_WIDTH;
                }

                if (velocity.y > 0) {
                    collisionY = testPointY * TILE_HEIGHT;
                } else if (velocity.y < 0) {
                    collisionY = (testPointY + 1) * TILE_HEIGHT;
                }

                // step 2: set collidedOn axis depending on which edge we collided with.
                if (collisionX != 0) {
                    collidedOn = static_cast<ObjectOwner::CollisionResult::Axis>(collidedOn |
                                                                                ObjectOwner::CollisionResult::Axis::Horizontal);
                }
                if (collisionY != 0) {
                    collidedOn = static_cast<ObjectOwner::CollisionResult::Axis>(collidedOn |
                                                                                ObjectOwner::CollisionResult::Axis::Vertical);
                }

                // step 3: if we have collided on both axes, then we are done.  Otherwise, continue iterating.
                if (collidedOn == ObjectOwner::CollisionResult::Axis::Both) {
                    std::cout << "    Collision detected at point: " << collisionX
                              << ", " << collisionY << ", "
                              << testPoint << std::endl;
                    return {collidedOn, velocity, futureBlock, &tileType};
                }

                // step 4:

            }
        }

        std::cout << "    No collision detected." << std::endl;
        return ObjectOwner::CollisionResult{ObjectOwner::CollisionResult::None,
                                            velocity, 0, nullptr};


        // step 1: use an epsilon value to iterate along the vector until we
        // hit a solid tile. If we hit a solid tile, determine which edge we touched, and note that as a clamp for that axis.
        // continue to iterate along vector, but always apply the clamp on the clamped dimension. terminate iteration if
        // both dimensions are clamped.
        // if no hits, return the original vector.

    }
} // namespace ur

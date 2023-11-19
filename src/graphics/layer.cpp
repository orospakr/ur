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

namespace ur {

// class constructor
    Layer::Layer(const MapLayer *mapLayer, const AGM *agm, int layerIndex, SDL_Texture *tileset,
                 SDL_Renderer *renderer) {
        tilepile = tileset;
        tilesAnimPos = 0;
        this->layerIndex = layerIndex;
        this->mapLayer = mapLayer;
        this->agm = agm;

        // populate floorGraphicalMap
        for (int ycounter = 0; ycounter < MAP_HEIGHT; ycounter++) {
            for (int xcounter = 0; xcounter < MAP_WIDTH; xcounter++) {
                floorGraphicalMap[xcounter][ycounter] =
                        mapLayer->tiles(xcounter + (ycounter * MAP_WIDTH));
            }
        }
    }

// class destructor
    Layer::~Layer() {}

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
                // std::cout << "The requested tilepile blit's source coordinates and
                // dimensions are: "; std::cout << " X origin: " << srcRect->x << " Y
                // origin: " << srcRect->y << " Height: " << srcRect->h << " Width: " <<
                // srcRect->w << std::endl; std::cout << "The requested renderer
                // destination coordinates and dimensions are: "; std::cout << " X origin:
                // " << dstRect->x << " Y origin: " << dstRect->y << " Height: " <<
                // dstRect->h << " Width: " << dstRect->w << std::endl;
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
    Layer::checkMapPathCollision(Object *obj, Sint64 xpos, Sint64 ypos, Sint64 xvel,
                                 Sint64 yvel) {
        Sint64 futureX =
                xpos + xvel; // values that could be... but only if the APM permits it!
        Sint64 futureY = ypos + yvel;
        int futureBlock;

        // TODO: the limitation with this approach is that it only checks destination tile,
        // not the path. so if velocity is too high, you'll glitch through walls.
        futureBlock = this->floorGraphicalMap[(futureX + 15) / TILE_WIDTH]
        [(futureY + 25) / TILE_HEIGHT];

        auto tiletypes = this->agm->tiletypes();

        auto tileType = this->agm->tiletypes()[futureBlock];

        if (tileType.solid()) {
            return ObjectOwner::CollisionResult{true, futureX, futureY, futureBlock, &tileType};
        } else {
            return ObjectOwner::CollisionResult{false, 0, 0, 0, nullptr};
        }
    }

} // namespace ur

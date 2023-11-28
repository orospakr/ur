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

/*
 * A display layer.  Lots of props, such as its layer index, transparency
 * settings and other goodies. :)
 */

#ifndef UR_LAYER_H
#define UR_LAYER_H

#include "ur.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "game/object.h"
#include "game/object_owner.h"
#include "proto/agm.pb.h"

namespace ur {

/*typedef struct
{
    Sint64 screenOrigin_X;
    Sint64 screenOrigin_Y;
    Sint64 objectOrigin_X;
    Sint64 objectOrigin_Y;
} UR_RELATIVE_ORIGIN; */

// enum UR_LAYER_ENUM { urLayerA, urLayerB, urLayerC };

class Layer : public ObjectOwner {
  public:
    /**
     * @brief Construct a new Layer object
     *
     * @param mapLayer MapLayer protobuf object.
     * @param layerIndex index of the layer, 0 is lowest.
     * @param tileset SDL texture of the whole animated tileset.
     * @param renderer SDL renderer to draw on.
     */
    Layer(const MapLayer *mapLayer, const std::shared_ptr<AGM> agm,
          int layerIndex, SDL_Texture *tileset, SDL_Renderer *renderer);

    // class destructor
    ~Layer();

    /* The tile graphics for this floor
     */
    SDL_Texture *tilepile;

    Sint64 drawToScreen(SDL_Renderer *renderer, SDL_Rect screenGeom);

    Sint64 run();

    /**
     * @brief Register an object to participate in this layer's physics run.
     *
     * @param obj
     */
    void registerObject(ur::Object *obj) override;

    ObjectOwner::CollisionResult
    checkMapPathCollision(Object *obj, Point2D position,
                          Vector2D velocity) override;

  private:
    /* Between 0 and 7.  Is the animation position for the tiles.
     */
    Sint64 tilesAnimPos;

    /* The layer's index.  Indexed from lowest to highest.
     */
    int layerIndex;

    /* the matrix of values describing to the engine what each block is
     * graphically. Remember, each block is 32x32
     */
    Sint64 floorGraphicalMap[MAP_WIDTH][MAP_HEIGHT];

    /**
     * @brief Level contents
     *
     */
    const MapLayer *mapLayer;

    const std::shared_ptr<AGM> agm;

    /*
     * returns an SDL_Rect that you can use as a srcrect when
     * blitting a tile from the tilepile
     */
    SDL_Rect *getTileSrcCoord(Sint64 number);

    /* returns an SDL_Rect that you can use as a dstrect when
     * blitting a tile from the tilepile
     */
    SDL_Rect *getTileDestCoord(Sint64 x, Sint64 y);

    /* debugging funcs to display the contents of floorGraphicalMap and physmap
     */
    void quickAGMPrint();

    /**
     * @brief Registered objects.
     *
     */
    std::vector<Object *> registeredObjects;
};

} // namespace ur

#endif // UR_LAYER_H

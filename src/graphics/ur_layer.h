/*
    This file is part of Usurper's Retribution.

    Usurper's Retribution is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
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

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "ur.h"

/* Forward declaration of ur_object instead of an #include "ur_object.h" to
 * avoid a cyclic dependency
 */
class ur_object;



/*typedef struct
{
    Sint64 screenOrigin_X;
    Sint64 screenOrigin_Y;
    Sint64 objectOrigin_X;
    Sint64 objectOrigin_Y;
} UR_RELATIVE_ORIGIN; */

enum UR_LAYER_ENUM
{
  urLayerA,
  urLayerB,
  urLayerC
};

class ur_layer
{
public:
  // class constructor
  ur_layer (std::string layerPath, UR_LAYER_ENUM position, bool transparent,
	    SDL_Surface * tileset, SDL_PixelFormat * screenFormat,
	    ur_object ** objPile);

  // class destructor
  ~ur_layer ();

  /* The object stack for the parent map */
  ur_object **objects;

  /* The tile graphics for this floor
   */
  SDL_Surface *tilepile;

  /* the matrix of values describing to the engine what each block is
   * graphically. Remember, each block is 32x32
   */
  Sint64 floorGraphicalMap[MAP_WIDTH][MAP_HEIGHT];

  /* the physical properties of the map, as described in docs/physmaps
   */
  Sint64 floorPhysicalMap[MAP_WIDTH][MAP_HEIGHT];

  Sint64 drawToScreen (SDL_Surface * screen, SDL_Rect screenGeom);

  Sint64 run ();

private:
  /* Between 0 and 7.  Is the animation position for the tiles.
   */
  Sint64 tilesAnimPos;

  /*
   * returns an SDL_Rect that you can use as a srcrect when
   * blitting a tile from the tilepile
   */
  SDL_Rect *getTileSrcCoord (Sint64 number);

  /* returns an SDL_Rect that you can use as a dstrect when
   * blitting a tile from the tilepile
   */
  SDL_Rect *getTileDestCoord (Sint64 x, Sint64 y);

  /* Loads up the floormaps.  Floormaps are used to determine
   * the way that the engine should react to different
   * floor styles on the map, and to graphically draw the map.
   * The two map types are Acorn Graphical Map (agm) and Acorn
   * Physical Map (apm).
   */
  Sint64 loadLayerMap (std::string agmFilename, std::string apmFilename);

  /* debugging funcs to display the contents of floorGraphicalMap and physmap
   */
  void quickAGMPrint ();
  void quickAPMPrint ();
};

#endif // UR_LAYER_H

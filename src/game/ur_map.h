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


#ifndef UR_MAP_H
#define UR_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "SDL.h"
#include "ur.h"
#include "ur_audio.h"
#include "ur_font.h"
#include "ur_layer.h"
#include "ur_object.h"

/*
 * A UR 'level.'  Contains all the layers, objects, characters, sprites,
 * textures, etc.  It will render to an SDL_Surface if you ask it
 * nicely.
 */

class ur_map
{
public:
  // class constructor
  ur_map (std::string name, SDL_PixelFormat * screenFormat, ur_font * fonts, ur_audio * audio);
  // class destructor
  ~ur_map ();
  std::string mapName;

  /* screen size and current display position (the x and y vars can be
   * bigger than the screen itself!) */
  SDL_Rect screenGeom;

  SDL_Surface *mapTileset;

  ur_layer *layerA;
  ur_layer *layerB;
  ur_layer *layerC;

  ur_object *player;

  /* the object pile. (this is for all the layers!)
   */
  ur_object **objects;

  /**
   * @brief Runs one cycle of updates for the map and all its objects.
   */
  Sint64 run (UR_DIRECTION_ENUM keypress, SDL_Surface * destinationSurface);
private:
  /* a pointer to the object that is the user's character
   */
  ur_object * playerCharacter;
  ur_font *fontManager;		// a pointer to the UR font manager
  ur_audio * audioController;
};

#endif // UR_MAP_H

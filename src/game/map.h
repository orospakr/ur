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
#include "audio/audio.h"
#include "graphics/font.h"
#include "graphics/layer.h"
#include "game/object.h"

namespace ur
{

  /*
   * A UR 'level.'  Contains all the layers, objects, characters, sprites,
   * textures, etc.  It will render to an SDL_Surface if you ask it
   * nicely.
   */

  class Map
  {
  public:
    // class constructor
    Map(std::string name, SDL_PixelFormat *screenFormat, Font *fonts, Audio *audio);
    // class destructor
    ~Map();
    std::string mapName;

    /* screen size and current display position (the x and y vars can be
     * bigger than the screen itself!) */
    SDL_Rect screenGeom;

    SDL_Surface *mapTileset;

    Layer *layerA;
    Layer *layerB;
    Layer *layerC;

    Object *player;

    /* the object pile. (this is for all the layers!)
     */
    Object **objects;

    /**
     * @brief Runs one cycle of updates for the map and all its objects.
     */
    Sint64 run(UR_DIRECTION_ENUM keypress, SDL_Surface *destinationSurface);

  private:
    /* a pointer to the object that is the user's character
     */
    Object *playerCharacter;
    Font *fontManager; // a pointer to the UR font manager
    Audio *audioController;
  };

}

#endif // UR_MAP_H
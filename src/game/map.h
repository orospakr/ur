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

#ifndef UR_MAP_H
#define UR_MAP_H

#include "audio/audio.h"
#include "game/object.h"
#include "graphics/font.h"
#include "graphics/layer.h"
#include "ur.h"
#include "proto/agm.pb.h"
#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

namespace ur {

/*
 * A UR 'level.'  Contains all the layers, objects, characters, sprites,
 * textures, etc.  It will render to an SDL_Surface if you ask it
 * nicely.
 */

class Map {
public:
  // class constructor
  Map(std::string name, SDL_Renderer *renderer, Font *fonts, Audio *audio);

  // class destructor
  ~Map();
  std::string mapName;

  /* screen size and current display position (the x and y vars can be
   * bigger than the screen itself!) */
  SDL_Rect screenGeom;

  SDL_Texture *mapTileset;

  /**
   * @brief Vector of layer objects.
   * 
   */
  std::vector<Layer *> layers;

  Object *player;

  /* the object pile. (this is for all the layers!)
   */
  Object **objects;

  /**
   * @brief Runs one cycle of updates for the map and all its objects.
   */
  Sint64 run(UR_DIRECTION_ENUM keypress, SDL_Renderer *renderer);

  /**
   * @brief Renders the map to the screen.
   */
  void drawToScreen(SDL_Renderer *renderer);

private:
  AGM definition;

  /* a pointer to the object that is the user's character
   */
  Object *playerCharacter;
  Font *fontManager; // a pointer to the UR font manager
  Audio *audioController;

  /**
   * @brief Load the map from the AGM protobuf file.
   * 
   * @param agmFilename 
   */
  void loadFromAGM(std::string agmFilename);
};

} // namespace ur

#endif // UR_MAP_H
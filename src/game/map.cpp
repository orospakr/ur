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

#include <SDL_image.h>

#include "game/map.h" // class's header file

namespace ur
{

  // class constructor
  Map::Map(std::string name,
           SDL_Renderer *renderer,
           Font *fonts,
           Audio *audio)
  {
    mapName = name;
    audioController = audio;
    fontManager = fonts;
    screenGeom.y = 0;
    screenGeom.x = 0;
    screenGeom.h = SCREEN_HEIGHT;
    screenGeom.w = SCREEN_WIDTH;

    /* initialise the object pointers
     */
    objects = new Object *[MAX_OBJS];
    // just 'cause, I'm gonna initialise all of those pointers to null
    for (Sint64 counter = 0; counter < MAX_OBJS; counter++)
    {
      objects[counter] = NULL;
    }

    /* load up the tiles for this map into a temp surface */
    SDL_Surface *mapTilesetLoad;

    std::string tilesetPath = "data/maps/" + mapName + "/tiles.png";
    mapTileset = IMG_LoadTexture(renderer, tilesetPath.c_str());
    if (mapTileset == NULL)
    {
      std::cout << "!! Unable to load tileset image from " << tilesetPath << " because " << SDL_GetError() << std::endl;
      exit(1);
    }

    /* instantiate the layers... */
    layerA =
        new Layer("data/maps/" + name + "/", urLayerA, false, mapTileset,
                  renderer, objects);
    layerB =
        new Layer("data/maps/" + name + "/", urLayerB, false, mapTileset,
                  renderer, objects);
    layerC =
        new Layer("data/maps/" + name + "/", urLayerC, false, mapTileset,
                  renderer, objects);
    // layerAtmosphere = new Layer("data/maps/"+name+"/",urLayerAtmosphere, false);  ATMOSPHERE NOT YET SUPPORTED
    player = new Object("data/objs/", "al", renderer, layerA);
    objects[0] = player;

    // we are going to create a Mickey Mouse, and then set his bit to 'evil'... let us see what happens...
    objects[1] = new Object("data/objs/", "mickey", renderer, layerA);
    objects[1]->faction = urFact_BadNik; // make him evil
    objects[0]->faction = urFact_FF;     // make our friend Al an FF
    player->xpos = 13 * TILE_WIDTH;
    player->ypos = 9 * TILE_HEIGHT;
    objects[1]->xpos = 12 * TILE_WIDTH;
    objects[1]->ypos = 13 * TILE_HEIGHT;
    audioController->pushBGM("7thheaven.mod");
  }

  Sint64
  Map::run(UR_DIRECTION_ENUM keypress, SDL_Renderer *renderer)
  {

    layerA->run();
    layerB->run();
    layerC->run();
    for (Sint64 counter = 0; counter < MAX_OBJS; counter++)
    {
      if (objects[counter] != NULL)
      {
        objects[counter]->run();
      }
    }
    player->move(keypress);

    // screen follows the player:
    screenGeom.x = player->xpos - (SCREEN_WIDTH / 2);
    screenGeom.y = player->ypos - (SCREEN_HEIGHT / 2);

    // now, we need to check to ensure that the screen position has not gone out of bounds:
    if (screenGeom.x <= 0)
    {
      screenGeom.x = 0;
    }

    if (screenGeom.x >= SCREEN_WIDTH * 2)
    {
      screenGeom.x = SCREEN_WIDTH * 2;
    }

    if (screenGeom.y <= 0)
    {
      screenGeom.y = 0;
    }

    if (screenGeom.y >= SCREEN_HEIGHT * 2)
    {
      screenGeom.y = SCREEN_HEIGHT * 2;
    }

    return 0;
  }

  void Map::drawToScreen(SDL_Renderer *renderer)
  {

    // std::cout<< player->xpos << std::endl << player->ypos << std::endl << std::endl;
    // screenGeom.y++;
    // screenGeom.x++;
    layerA->drawToScreen(renderer, screenGeom);
    for (Sint64 counter = 0; counter < MAX_OBJS; counter++)
    {
      if (objects[counter] != NULL)
      {
        objects[counter]->drawToScreen(renderer, screenGeom);
      }
    }
    layerB->drawToScreen(renderer, screenGeom);
    layerC->drawToScreen(renderer, screenGeom);

    SDL_Point greetzTextPos;
    greetzTextPos.x = 3;
    greetzTextPos.y = SCREEN_HEIGHT - 20;
    SDL_Color funkycolor;
    funkycolor.r = 255;
    funkycolor.g = 255;
    funkycolor.b = 255;
    fontManager->printTextToSurface(renderer, "ur0.0.1 Demo!",
                                    urFont_Big, greetzTextPos, funkycolor);

    if (player->dead)
    {
      SDL_Point gameOverPos;
      SDL_Color gameOverClr;
      gameOverClr.r = 255;
      gameOverClr.g = 0;
      gameOverClr.b = 0;
      gameOverPos.y = (SCREEN_HEIGHT / 2) - (FONT_TEXT_Y / 2);
      gameOverPos.x = (SCREEN_WIDTH / 2) - ((FONT_TEXT_X * 10) / 2);
      fontManager->printTextToSurface(renderer, "Game Over!", urFont_Big, gameOverPos, gameOverClr);
    }
  }

  // class destructor
  Map::~Map()
  {
    delete layerA;
    // delete layerB;
    // delete layerC;
    delete[] objects; // note the objects that this array of pointers points to will also require freeing
    SDL_DestroyTexture(mapTileset);
    delete audioController;
    // delete layerAtmosphere;  ATMOSPHERE NOT YET SUPPORTED
  }
}
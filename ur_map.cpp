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


#include "ur_map.h"		// class's header file

// class constructor
ur_map::ur_map (std::string name, SDL_PixelFormat * screenFormat,
		ur_font * fonts, ur_audio * audio)
{
  /* just a few quick initialisations...
   */
  mapName = name;
  audioController = audio;
  fontManager = fonts;
  screenGeom.y = 0;
  screenGeom.x = 0;
  screenGeom.h = SCREEN_HEIGHT;
  screenGeom.w = SCREEN_WIDTH;



  /* initialise the object pointers
   */
  objects = new ur_object *[MAX_OBJS];
  // just 'cause, I'm gonna initialise all of those pointers to null
  for (Sint64 counter = 0; counter < MAX_OBJS; counter++)
    {
      objects[counter] = NULL;
    }

  /* load up the tiles for this map into a temp surface */
  SDL_Surface *mapTilesetLoad;
  mapTilesetLoad =
    SDL_LoadBMP (("data/maps/" + name + "/tiles.bmp").c_str ());
  /* convert them to the display's format for better performance, set the colourkey and finish up */
  mapTileset = SDL_DisplayFormat (mapTilesetLoad);
  SDL_SetColorKey (mapTileset, SDL_SRCCOLORKEY,
		   SDL_MapRGB (screenFormat, 255, 255, 255));
  SDL_FreeSurface (mapTilesetLoad);

  /* instantiate the layers... */
  layerA =
    new ur_layer ("data/maps/" + name + "/", urLayerA, false, mapTileset,
		  screenFormat, objects);
  layerB =
    new ur_layer ("data/maps/" + name + "/", urLayerB, false, mapTileset,
		  screenFormat, objects);
  layerC =
    new ur_layer ("data/maps/" + name + "/", urLayerC, false, mapTileset,
		  screenFormat, objects);
  //layerAtmosphere = new ur_layer("data/maps/"+name+"/",urLayerAtmosphere, false);  ATMOSPHERE NOT YET SUPPORTED
  player = new ur_object ("data/objs/", "al", screenFormat, layerA);
  objects[0] = player;

  // we are going to create a Mickey Mouse, and then set his bit to 'evil'... let us see what happens...
  objects[1] = new ur_object ("data/objs/", "mickey", screenFormat, layerA);
  objects[1]->faction = urFact_BadNik;	// make him evil
  objects[0]->faction = urFact_FF;	// make our friend Al an FF
  player->xpos = 13 * TILE_WIDTH;
  player->ypos = 9 * TILE_HEIGHT;
  objects[1]->xpos = 12 * TILE_WIDTH;
  objects[1]->ypos = 13 * TILE_HEIGHT;
  audioController->pushBGM("7thheaven.mod");
}

Sint64
ur_map::run (UR_DIRECTION_ENUM keypress, SDL_Surface * destinationSurface)
{
  
  layerA->run ();
  layerB->run ();
  layerC->run ();
  for (Sint64 counter = 0; counter < MAX_OBJS; counter++)
    {
      if (objects[counter] != NULL)
	{
	  objects[counter]->run ();
	}
    }
  player->move (keypress);
  screenGeom.x = player->xpos - (SCREEN_WIDTH / 2);
  screenGeom.y = player->ypos - (SCREEN_HEIGHT / 2);

  // now, we need to check to ensure that the screen position has not gone beyond the bounds.
  
  if (screenGeom.x <= 0)
    {
      screenGeom.x = 0;
    }

  if (screenGeom.x >= SCREEN_WIDTH *2 )
    {
      screenGeom.x = SCREEN_WIDTH*2;
    }

  if (screenGeom.y <= 0)
    {
      screenGeom.y = 0;
    }

  if (screenGeom.y >= SCREEN_HEIGHT*2)
    {
      screenGeom.y = SCREEN_HEIGHT*2;
    }
  
  
  //cout<< player->xpos << endl << player->ypos << endl << endl;
  //screenGeom.y++;
  //screenGeom.x++;
  layerA->drawToScreen (destinationSurface, screenGeom);
  for (Sint64 counter = 0; counter < MAX_OBJS; counter++)
    {
      if (objects[counter] != NULL)
	{
	  objects[counter]->drawToScreen (destinationSurface, screenGeom);
	}
    }
  layerB->drawToScreen (destinationSurface, screenGeom);
  layerC->drawToScreen (destinationSurface, screenGeom);

  SDL_Rect greetzTextPos;
  greetzTextPos.h = 500;
  greetzTextPos.w = 500;
  greetzTextPos.x = 3;
  greetzTextPos.y = 460;
  SDL_Color funkycolor;
  funkycolor.r = 0;
  funkycolor.g = 0;
  funkycolor.b = 0;
  fontManager->printTextToSurface (destinationSurface, "ur0.0.1 Demo!",
				   urFont_Big, greetzTextPos, 0, funkycolor);
				   
  if (player->dead)
  {
    SDL_Rect gameOverPos;
    SDL_Color gameOverClr;
    gameOverClr.r = 255;
    gameOverClr.g = 0;
    gameOverClr.b = 0;
    gameOverPos.w = FONT_TEXT_X * 10;
    gameOverPos.h = FONT_TEXT_Y * 1;
    gameOverPos.y = (SCREEN_HEIGHT / 2 ) - (FONT_TEXT_Y / 2 );
    gameOverPos.x = (SCREEN_WIDTH / 2 ) - ((FONT_TEXT_X * 10) /2);
    fontManager->printTextToSurface (destinationSurface, "Game Over!",urFont_Big, gameOverPos, 0, gameOverClr);
  }
  return 0;
}

// class destructor
ur_map::~ur_map ()
{
  delete layerA;
  delete layerB;
  delete layerC;
  delete [] objects;		// note the objects that this array of pointers points to will also require freeing
  SDL_FreeSurface (mapTileset);
  delete audioController;
  // delete layerAtmosphere;  ATMOSPHERE NOT YET SUPPORTED
}

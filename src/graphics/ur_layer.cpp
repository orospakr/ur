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

#include "ur_layer.h" // class's header file

namespace ur
{

  // class constructor
  Layer::Layer(std::string layerPath, UR_LAYER_ENUM position,
               bool transparent, SDL_Surface *tileset,
               SDL_PixelFormat *screenFormat, Object **objPile)
  {
    tilepile = tileset;
    objects = objPile;
    tilesAnimPos = 0;

    // yuckyBuffer=SDL_CreateRGBSurface(SDL_SWSURFACE, 640,480,(*screenFormat).BitsPerPixel,(*screenFormat).Rmask, (*screenFormat).Gmask, (*screenFormat).Bmask, (*screenFormat).Amask);

    /* Now we need to load up the map (the array of ints called floorMap) */
    std::string agmFilename; // graphic map filename
    std::string apmFilename; // physical map filename
    switch (position)
    {
    case urLayerA:
      agmFilename = "layerA.agm";
      apmFilename = "layerA.apm";
      break;
    case urLayerB:
      agmFilename = "layerB.agm";
      apmFilename = "layerB.apm";
      break;
    case urLayerC:
      agmFilename = "layerC.agm";
      apmFilename = "layerC.apm";
      break;
    }
    /* Now we need to load up the two maps...
     */
    loadLayerMap(layerPath + agmFilename, layerPath + apmFilename);
  }

  // class destructor
  Layer::~Layer()
  {
  }

  /*
   * Load up a floormap.  Floormaps are used to determine
   * the way that the engine should react to different
   * floor styles on the map, and to draw the map's surface
   */
  Sint64
  Layer::loadLayerMap(std::string agmFilename, std::string apmFilename)
  {
    std::ifstream loadReader; /* This object is used to load up the map matrix
                               */
    /* This code loads up the agm */
    loadReader.open((agmFilename).c_str(), std::ifstream::in);
    if (!loadReader.good())
    {
      printf("!! Unable to open graphical map definition file (agm).\n");
      printf(("   Filename was " + agmFilename + "\n").c_str());
      exit(1); // call system to stop
    }
    for (Sint64 ycounter = 0; ycounter < MAP_HEIGHT; ycounter++)
    {
      for (Sint64 xcounter = 0; xcounter < MAP_WIDTH; xcounter++)
      {
        char *c_str_buf = new char[5];
        loadReader.getline(c_str_buf, 5, ',');
        floorGraphicalMap[xcounter][ycounter] = atoi(c_str_buf);
        delete[] c_str_buf;
      }
    }
    loadReader.close();

    /* This code loads up the apm */
    loadReader.open((apmFilename).c_str(), std::ifstream::in);
    if (!loadReader.good())
    {
      printf("!! Unable to open physical map definition file (apm).\n");
      printf(("   Filename was " + apmFilename + "\n").c_str());
      exit(1); // call system to stop
    }
    for (Sint64 ycounter = 0; ycounter < MAP_HEIGHT; ycounter++)
    {
      for (Sint64 xcounter = 0; xcounter < MAP_WIDTH; xcounter++)
      {
        char *c_str_buf = new char[5];
        loadReader.getline(c_str_buf, 5, ',');
        floorPhysicalMap[xcounter][ycounter] = atoi(c_str_buf);
        delete[] c_str_buf;
      }
    }
    loadReader.close();
    return 0;
  }

  Sint64
  Layer::drawToScreen(SDL_Surface *screen, SDL_Rect screenGeom)
  {
    Sint64 beginY = screenGeom.y / 32;
    Sint64 endY = beginY + (SCREEN_HEIGHT / 32);
    Sint64 beginX = screenGeom.x / 32;
    Sint64 endX = beginX + (SCREEN_WIDTH / 32);

    endX += 2; // these two are there just so it overlaps and there's no blockiness at the right and bottom edges
    endY += 2;

    // std::cout << screenGeom.w/32 << std::endl << screenGeom.h/32 << std::endl << std::endl;
    for (Sint64 ycounter = beginY; ycounter < endY; ycounter++)
    {
      for (Sint64 xcounter = beginX; xcounter < endX; xcounter++)
      {
        SDL_Rect *srcRect;
        SDL_Rect *dstRect;
        srcRect = getTileSrcCoord(floorGraphicalMap[xcounter][ycounter]);
        dstRect = getTileDestCoord(xcounter, ycounter);
        // std::cout << "The requested tilepile blit's source coordinates and dimensions are: ";
        // std::cout << " X origin: " << srcRect->x << " Y origin: " << srcRect->y << " Height: " << srcRect->h << " Width: " << srcRect->w << std::endl;
        // std::cout << "The requested screen destination coordinates and dimensions are: ";
        // std::cout << " X origin: " << dstRect->x << " Y origin: " << dstRect->y << " Height: " << dstRect->h << " Width: " << dstRect->w << std::endl;
        dstRect->x -= screenGeom.x;
        dstRect->y -= screenGeom.y;
        SDL_BlitSurface(tilepile, srcRect, screen, dstRect);
        delete srcRect;
        delete dstRect;
      }
    }
    return 0;
  }

  SDL_Rect *
  Layer::getTileSrcCoord(Sint64 number)
  {
    SDL_Rect *result = new SDL_Rect;
    result->h = TILE_HEIGHT;
    result->w = TILE_WIDTH;
    result->x = TILE_WIDTH * (number - 1);
    result->y = TILE_HEIGHT * tilesAnimPos;
    return result;
  }

  SDL_Rect *
  Layer::getTileDestCoord(Sint64 x, Sint64 y)
  {
    SDL_Rect *result = new SDL_Rect;
    result->h = TILE_HEIGHT;
    result->w = TILE_WIDTH;
    result->x = TILE_WIDTH * x;
    result->y = TILE_HEIGHT * y;
    return result;
  }

  void
  Layer::quickAGMPrint()
  {
    for (Sint64 ycounter = 0; ycounter < MAP_HEIGHT; ycounter++)
    {
      for (Sint64 xcounter = 0; xcounter < MAP_WIDTH; xcounter++)
      {
        std::cout << floorGraphicalMap[xcounter][ycounter];
      }
      std::cout << "\n";
    }
  }

  void
  Layer::quickAPMPrint()
  {
    for (Sint64 ycounter = 0; ycounter < MAP_HEIGHT; ycounter++)
    {
      for (Sint64 xcounter = 0; xcounter < MAP_WIDTH; xcounter++)
      {
        std::cout << floorPhysicalMap[xcounter][ycounter];
      }
      std::cout << "\n";
    }
  }

  Sint64
  Layer::run()
  {
    tilesAnimPos = SDL_GetTicks() / 33 / 3 % 8;
    return 0;
  }

}

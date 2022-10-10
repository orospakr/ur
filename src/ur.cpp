/*         USURPER's RETRIBUTION      */
/*     Copyright 2002-2003 Orospakr   */
/* A quick summary:
   UR is an RPG game for the GNU System, using SDL for multimedia I/O.  It is
   quite portable, requiring only the GNU System and the SDL library,
   and should compile and run on X11(fb?)/GNU/Linux, Win32(mingw32 or perhaps cygwin),
   Sony PS2(with GNU/Linux), and maybe even the Dreamcast. Endianess was in mind
   during design and coding.  If you are using a PowerPC or other such machine,
   and see anything that looks 'inverted' or 'backwards,' it is likely an endianness
   bug (please email a bug report to bsdnerd@yahoo.ca!)  It is based
   on the Archie/SatAM SonicVerse (roughly) as the game world.
   Another issue seems to be memory issues, ie conflicts, leaks, uninitialisations...
   please help me find these if you know C++! :)
   Game MODs should be fairly easy to write, as it will (eventually)
   utilise a a WAD-like file containing a directory structure with the
   game data.  I am toying with different format ideas... reqs:
    - no compression required.  The formats will be PNG and OGG,
      (maybe some Modfiles for DA thrown in, too...)
      and compression would be slow and redundant
    - it needs to be random access (no go for tarballs)
    - needs to be multi-file (obviously) and have support for
      directory trees/structures (no go for BZ2 or GZ!)
    - royalty-free.  (I want this program to be as true to the GNU
      ideal as possible... Hell, Freedom is what the game characters
      are fighting for!) (Zip dies here, I think...)
   I think this effectively disallows RAR, ZIP, TAR, GZ and BZ2 for varying
   reasons...  darnit...  Maybe just a direct directory structure on the FS...

   It is Free Software, (as in both free speech and free beer)
   and it is released under the GNU General Public Licence.

   The tile size is 32x32.  There will be four layers to the
   game display, namely:
      - floor layer A (bottommost)
      - floor layer B
      - floor layer C (foremost)
      - atmospheric effect layer (fog?)
   Sprites each have their own surfaces, and they are blitted onto
   the floor layers on each rendering cycle.  The animations, too, are
   cycled on each render.  The levels are rendered from a matrix of
   ints defining a map.  There are two types of these.  The physical map and
   the graphical map.  The graphical map contains the data that makes the engine
   render the layer from the tiles, and the physical map is used to define the
   physical attributes (can walk there, can't walk there...)

   In a more high level context, the characters will move through the game
   by crossing into special blocks that will pop them into another map
   (with in a suitable IC context, of course... the most common one being
   a door :P)

   Also, there will be, perhaps, a third map which defines arguments for the physical
   map blocks.  Such as, which level to jump to when you enter a jump block.

   The way you will interact with other characters will be by
   'text referencing'.  Each char in the map has an array of words to
   react to and their respective responses.  For instance, if you query
   a Knothole Village shopkeeper on 'donuts' he might respond with:
      'Laughs at you heartily.  "You aren't from these parts, are you,
      son?"'
   There will also be default 'look' and 'name' responses built in, and perhaps
   'buy' and 'sell' if that particular character supports that.

   It is (mostly) object oriented.  ( I bet some OOP diehards will look at this code
   and keel over dead, tho... >.> )
*/

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

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>

#include <SDL2/SDL.h>

#include "ur.h"

#include "graphics/font.h"
#include "ui/titlescreen.h"
#include "game/object.h"
#include "graphics/layer.h"
#include "ui/menu.h"
#include "game/map.h"

/**
 * SDL window.
 */
SDL_Window *sdlWindow;

/**
 * SDL renderer.
 */
SDL_Renderer *sdlRenderer;

/* this is an instantiation of the game itself, including the primary maps... this thing
   contains all of the layers, objects, sprites, and everything else that make up the
   currently loaded location in the game world
*/
ur::Map *map = NULL;

/* The font manager */
ur::Font *fontManager = NULL;

/* The title screen */
ur::Titlescreen *titleScreen = NULL;

/* this is the menuing subsystem.  The main game loop switches between this and the Map
   accordingly.
*/
ur::Menu *menu = NULL;

/* the audio manager */
ur::Audio *audioManager = NULL;

/**
 * Wallclock at last iteration.
 */
static Uint32 lastTime = 0;

void inputUpdateKey(SDL_Event *sdlevents, ur::UR_INPUT *currentInput, bool down)
{
  ur::UR_KEYPAD_ENUM result;
  switch ((*sdlevents).key.keysym.sym)
  {
  case SDLK_LEFT:
    currentInput->left = down;
    break;
  case SDLK_RIGHT:
    currentInput->right = down;
    break;
  case SDLK_UP:
    currentInput->up = down;
    break;
  case SDLK_DOWN:
    currentInput->down = down;
    break;
  case SDLK_RETURN:
    currentInput->start = down;
    break;
  case SDLK_SPACE:
    currentInput->action = down;
    break;
  case SDLK_RCTRL:
    currentInput->select = down;
    break;
  default:
    break;
  }
}

ur::UR_DIRECTION_ENUM
keyToDirection(ur::UR_INPUT keypress)
{
  ur::UR_DIRECTION_ENUM result;

  if (keypress.up && keypress.right)
  {
    result = ur::urDirNorthEast;
  }
  else if (keypress.up && keypress.left)
  {
    result = ur::urDirNorthWest;
  }
  else if (keypress.down && keypress.right)
  {
    result = ur::urDirSouthEast;
  }
  else if (keypress.down && keypress.left)
  {
    result = ur::urDirSouthWest;
  }
  else if (keypress.up)
  {
    result = ur::urDirNorth;
  }
  else if (keypress.down)
  {
    result = ur::urDirSouth;
  }
  else if (keypress.left)
  {
    result = ur::urDirWest;
  }
  else if (keypress.right)
  {
    result = ur::urDirEast;
  }
  else
  {
    result = ur::urDirNone;
  }
  return result;
}

/* Primary start up routine, gets things warmed up and online... Hey, you gotta
   start somewhere. n.~ */
int main(int argc, char *argv[])
{
  char *msg;
  Sint64 done;
  std::cout << "\n~~~ USURPER's RETRIBUTION ~~~\n";
  std::cout << "    " << REVISION_EDITION << std::endl;
  std::cout << "       Version " << REVISION_MAJOR << "." << REVISION_MINOR << "."
            << REVISION_MICRO << std::endl
            << std::endl;
  printf("Initialising SDL... ");
  /* Initialize SDL */
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
  {
    asprintf(&msg, "Couldn't initialize SDL: %s\n", SDL_GetError());
    std::cout << msg;
    free(msg);
    exit(1);
  }
  // atexit (SDL_Quit);
  printf("DONE.\nCreating window...");
  /* Set 640x480 16-bits video mode */
  // screen =
  //     SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16,
  //                      SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);

  sdlWindow = SDL_CreateWindow("Usurper's Retribution", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, 800,
                               600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if (sdlWindow == NULL)
  {
    std::cout << "!! Could not create window: " << SDL_GetError() << std::endl;
    exit(1);
  }

  // Using software rendering for now because otherwise (at least on macOS with metal) there are subpixel rendering issues.
  sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC);
  if (sdlRenderer == NULL)
  {
    std::cout << "!! Could not create renderer: " << SDL_GetError() << std::endl;
    exit(1);
  }

  // clear the display
  SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
  SDL_RenderClear(sdlRenderer);
  SDL_RenderPresent(sdlRenderer);

  // our logical display size is 640x480, use GPU scaling to scale it up.
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); // nearest-neighbor scaling for sharp pixel art.
  SDL_RenderSetLogicalSize(sdlRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

  printf("DONE.\nDisplaying startup logo... ");
  std::string name = "Usurper's Retribution ";

  SDL_SetWindowTitle(sdlWindow, (name + REVISION_EDITION).c_str());

  audioManager = new ur::Audio;
  /* instantiate the system services, such as the sound and font managers */
  fontManager = new ur::Font("data/", sdlRenderer);

  // display the startup logos
  SDL_Surface *logoLoader;
  logoLoader = SDL_LoadBMP("data/logo_ld.bmp");
  SDL_Texture *logoTexture = SDL_CreateTextureFromSurface(sdlRenderer, logoLoader);
  SDL_FreeSurface(logoLoader);
  SDL_RenderCopy(sdlRenderer, logoTexture, NULL, NULL);

  SDL_RenderPresent(sdlRenderer);
  SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255);
  SDL_RenderClear(sdlRenderer);

  SDL_Point welcomeTextPos;
  welcomeTextPos.x = 10;
  welcomeTextPos.y = 10;
  SDL_Color textcolor;
  textcolor.r = 255;
  textcolor.g = 0;
  textcolor.b = 0;
  fontManager->printTextToSurface(sdlRenderer, "Welcome to UR!", ur::urFont_Big,
                                  welcomeTextPos, textcolor);

  // SDL_Delay(5000);             // show logo for 1 sec

  printf("DONE.\nStarting the engine... ");

  /* Start instantiating the game itself */
  titleScreen = new ur::Titlescreen("data/", sdlRenderer, fontManager, audioManager);

  menu = new ur::Menu();

  printf("DONE.\nOnline!!\n\n");
  done = 0;

  SDL_Event event;
  ur::UR_INPUT currentInput = ur::UR_INPUT_DEFAULT;

  ur::UR_RUN_STATE status = ur::urGameState_TitleScreen;
  lastTime = SDL_GetTicks();

  // time step in ms for the game logic (60 fps).
  // TODO: these should be floats to avoid rounding? timestep will be too short
  const Uint32 timeStep = 1000 / 60;
  const Uint32 graphicsTimeStep = 1000 / 60;
  // time accumulator for the game logic
  static Uint32 accumulator = 0;

  /* primary game loop! */
  while (!done)
  {
    // get current time in ms
    Uint32 currentTime = SDL_GetTicks();
    // calculate time since last iteration
    Uint32 timeSinceLast = currentTime - lastTime;
    // store current time for next iteration
    lastTime = currentTime;

    // add the time since last iteration to the accumulator
    accumulator += timeSinceLast;

    // calculate fps
    int fps = 1000 / timeSinceLast;
    // std::cout << "FPS: " << fps << std::endl;

    /* Process events */
    while (SDL_PollEvent(&event))
    {
      // I can change this to handle multiple keypresses at once by mutating a struct
      // or bitmask. Track SDL_KEYDOWN to clear them.
      switch (event.type)
      {
      case SDL_KEYDOWN:
        /* this bit puts the user's interactions in currentInput for relaying
         * to the proper subsystem
         */
        if (event.key.keysym.sym == SDLK_ESCAPE)
          done = 1;
        inputUpdateKey(&event, &currentInput, true);
        break;
      case SDL_KEYUP:
        inputUpdateKey(&event, &currentInput, false);
        break;
      case SDL_QUIT:
        done = 1;
        break;
      default:
        break;
      }
    }
    switch (status)
    {
    case ur::urGameState_Quit:
      done = 1;
      break;
    case ur::urGameState_InGame:
      // run physics and game logic at timeStep rate.
      while (accumulator >= timeStep)
      {
        float interpolationFactor = accumulator / timeStep;

        // run the game logic
        map->run(keyToDirection(currentInput), sdlRenderer);

        // remove the time step from the accumulator
        accumulator -= timeStep;
      }
      SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
      SDL_RenderClear(sdlRenderer);
      map->drawToScreen(sdlRenderer);
      SDL_RenderPresent(sdlRenderer);

      break;
    case ur::urGameState_TitleScreen:
      Sint64 titleResult;
      SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
      SDL_RenderClear(sdlRenderer);
      titleResult = titleScreen->run(currentInput, sdlRenderer);
      if (titleResult == 0)
      {
        map = new ur::Map("kv", sdlRenderer, fontManager, audioManager);
        status = ur::urGameState_InGame;
      }
      SDL_RenderPresent(sdlRenderer);
      break;
    default:
      done = 1;
      break;
    }

    // use delay limit frame rate to 60
    // if (timeSinceLast < (graphicsTimeStep))
    // {
    //   std::cout << "HOLD" << std::endl;
    //   SDL_Delay(graphicsTimeStep - timeSinceLast);
    // }

    // max of (graphicstimestep - timeSinceLast) or 0

    // don't need this, got vsync.
    // int timeUntilNextFrame = graphicsTimeStep - (SDL_GetTicks() - lastTime);
    // if (timeUntilNextFrame > 0)
    // {
    //   SDL_Delay(timeUntilNextFrame);
    // }
  }
  delete menu;
  delete map;
  delete titleScreen;
  delete fontManager;
  SDL_Quit();

  std::cout << "\nShutdown successful.  Welcome back to the world of shell.\n";
  return 0;
}

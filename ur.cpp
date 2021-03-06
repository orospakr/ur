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
#include "SDL.h"
#include "ur.h"

#include "ur_font.h"
#include "ur_titlescreen.h"
#include "ur_object.h"
#include "ur_layer.h"
#include "ur_menu.h"
#include "ur_map.h"

/* this is an instantiation of the game itself, including the primary maps... this thing
   contains all of the layers, objects, sprites, and everything else that make up the
   currently loaded location in the game world
*/
ur_map *map = NULL;

/* The font manager */
ur_font *fontManager = NULL;

/* The title screen */
ur_titlescreen *titleScreen = NULL;

/* this is the menuing subsystem.  The main game loop switches between this and the ur_map
   accordingly.
*/
ur_menu *menu = NULL;

/* The screen surface */
SDL_Surface *screen = NULL;	// what you can see onscreen

/* the audio manager */
ur_audio * audioManager = NULL;

/* This function draws to the screen the game map and the HUD */
static void
draw ()
{
  /* Make sure everything is displayed on screen */
  SDL_Flip (screen);
  /* Don't run too fast */
  SDL_Delay (1);
}

UR_KEYPAD_ENUM
getKey (SDL_Event * sdlevents)
{
  UR_KEYPAD_ENUM result;
  switch ((*sdlevents).key.keysym.sym)
    {
    case SDLK_LEFT:
      result = urKP_Left;
      break;
    case SDLK_RIGHT:
      result = urKP_Right;
      break;
    case SDLK_UP:
      result = urKP_Up;
      break;
    case SDLK_DOWN:
      result = urKP_Down;
      break;
    case SDLK_RETURN:
      result = urKP_Start;
      break;
    case SDLK_SPACE:
      result = urKP_Action;
      break;
    case SDLK_RCTRL:
      result = urKP_Select;
      break;
    default:
      result = urKP_None;
      break;
    }
  return result;
}

UR_DIRECTION_ENUM
keyToDirection (UR_KEYPAD_ENUM keypress)
{
  UR_DIRECTION_ENUM result;
  switch (keypress)
    {
    case urKP_Left:
      result = urDirWest;
      break;
    case urKP_Right:
      result = urDirEast;
      break;
    case urKP_Up:
      result = urDirNorth;
      break;
    case urKP_Down:
      result = urDirSouth;
      break;
    default:
      result = urDirNone;
      break;
    }
  return result;
}

/* Primary start up routine, gets things warmed up and online... Hey, you gotta
   start somewhere. n.~ */
int
main (int argc, char *argv[])
{
  char *msg;
  Sint64 done;
  std::cout << "\n~~~ USURPER's RETRIBUTION ~~~\n";
  std::cout << "    " << REVISION_EDITION << std::endl;
  std::cout << "       Version " << REVISION_MAJOR << "." << REVISION_MINOR << "."
    << REVISION_MICRO << std::endl << std::endl;
  printf ("Initialising SDL... ");
  /* Initialize SDL */
  if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
      asprintf (&msg, "Couldn't initialize SDL: %s\n", SDL_GetError ());
      std::cout << msg;
      free (msg);
      exit (1);
    }
  //atexit (SDL_Quit);
  printf ("DONE.\nSetting video mode (640x480x16bpp)... ");
  /* Set 640x480 16-bits video mode */
  screen =
    SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, 16,
		      SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN  );
  if (screen == NULL)
    {
      asprintf (&msg, "Couldn't set 640x480x16 video mode: %s\n",
		SDL_GetError ());
      std::cout << msg;
      free (msg);
      exit (2);
    }
  printf ("DONE.\nDisplaying startup logo... ");
  std::string name = "Usurper's Retribution ";
  SDL_WM_SetCaption ((name + REVISION_EDITION).c_str (), NULL);

  audioManager = new ur_audio;
  /* instantiante the system services, such as the sound and font managers */
  fontManager = new ur_font ("data/", screen->format);

  // display the startup logos
  SDL_Surface *logoLoader;
  logoLoader = SDL_LoadBMP ("data/logo_ld.bmp");
  SDL_BlitSurface (logoLoader, NULL, screen, NULL);
  SDL_Rect welcomeTextPos;
  welcomeTextPos.h = 500;
  welcomeTextPos.w = 500;
  welcomeTextPos.x = 10;
  welcomeTextPos.y = 10;
  SDL_Color textcolor;
  textcolor.r = 255;
  textcolor.g = 0;
  textcolor.b = 0;
  fontManager->printTextToSurface (screen, "Welcome to UR!", urFont_Big,
				   welcomeTextPos, 0, textcolor);
  SDL_Flip (screen);
  SDL_FreeSurface (logoLoader);	// free the memory!
  SDL_Delay (5000);		// show logo for 1 sec

  printf ("DONE.\nStarting the engine... ");

  /* Start instantiating the game itself */
  titleScreen = new ur_titlescreen ("data/", *(screen->format), fontManager, audioManager);
  
  menu = new ur_menu ();


  printf ("DONE.\nOnline!!\n\n");
  done = 0;

  /* primary game loop! */
  SDL_Event event;
  UR_KEYPAD_ENUM currentInput = urKP_None;

  /* current game status:
   * 0: quit
   * 1: in game
   * 2: in title screen
   * 
   */
  int status = 2;

  while (!done)
    {
      /* Check for basic events and keyboard */
      while (SDL_PollEvent (&event))
	{
	  switch (event.type)
	    {
	    case SDL_KEYDOWN:
	      /* this bit puts the user's interactions in currentInput for relaying
	       * to the proper subsystem
	       */
	      if (event.key.keysym.sym == SDLK_ESCAPE)
		done = 1;
	      currentInput = getKey (&event);
	      break;
	    case SDL_KEYUP:
	      currentInput = urKP_None;
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
	case 0:
	  done = 1;
	  break;
	case 1:
	  map->run (keyToDirection (currentInput), screen);
	  break;
	case 2:
	  Sint64 titleResult;
	  titleResult = titleScreen->run (currentInput, screen);
	  if (titleResult == 0)
	    {
	      map = new ur_map ("kv", screen->format, fontManager, audioManager);
	      status = 1;
	    }
	  break;
	default:
	  done = 1;
	  break;
	}
      /* Draw to screen */
      draw ();

      /* Horrible workaround for lack of linear time scaling. vaguely 30 Hz. */
      SDL_Delay(32);
    }
  delete menu;
  delete map;
  delete titleScreen;
  delete fontManager;
  SDL_Quit();

  std::cout << "\nShutdown sucessful.  Welcome back to the world of shell.\n";
  return 0;
}

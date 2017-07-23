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

#ifndef UR_TITLESCREEN_H
#define UR_TITLESCREEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream.h>
#include "SDL.h"
#include "ur.h"
#include "ur_audio.h"
#include "ur_map.h"
#include "ur_font.h"

/*
 * The title screen class.
 */
class ur_titlescreen
{
public:
  // class constructor
  ur_titlescreen (std::string basedir, SDL_PixelFormat screenFormat,
		  ur_font * fonts, ur_audio * audio);
  // class destructor
  ~ur_titlescreen ();
  /* runs the Title Screen one cycle.  Returns 0 if the user hit START and the game should begin
   *, otherwise just run it again.
   */
  Sint64 run (UR_KEYPAD_ENUM keystroke, SDL_Surface * screen);
private:
    SDL_Surface * titleGraphic;
  ur_font *fontManager;
    std::string scrollerText;
  Sint64 scrollerPos;
  ur_audio * audioManager;
};

#endif // UR_TITLESCREEN_H

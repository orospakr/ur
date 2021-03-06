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
 * UR's font manager.  Prints text out to a surface if you ask it nicely.
 */

#ifndef UR_FONT_H
#define UR_FONT_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "ur.h"


class ur_font
{
public:
  // class constructor
  ur_font (std::string basedir, SDL_PixelFormat * screenFormat);
  // class destructor
  ~ur_font ();
  void printTextToSurface (SDL_Surface * surface, std::string text,
			   UR_FONT_ENUM whichFont, SDL_Rect destPos,
			   Sint64 offset, SDL_Color textColor);
private:
    SDL_Surface * bigFont;
  SDL_Surface *textFont;
  Sint64 char2ascii (char input);
};

#endif // UR_FONT_H

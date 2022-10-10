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
#include <SDL2/SDL.h>
#include "ur.h"

namespace ur
{

  class Font
  {
  public:
    // class constructor
    Font(std::string basedir, SDL_Renderer *renderer);
    // class destructor
    ~Font();
    void printTextToSurface(SDL_Renderer * renderer, std::string text,
                            UR_FONT_ENUM whichFont, SDL_Point destPos,
                            SDL_Color textColor);

  private:
    SDL_Texture *bigFont;
    SDL_Texture *textFont;
    Sint64 char2ascii(char input);
  };

}

#endif // UR_FONT_H

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

#include "graphics/font.h" // class's header file
#include <SDL_image.h>
#include <string>

namespace ur {

// class constructor
Font::Font(std::string basedir, SDL_Renderer *renderer) {
  bigFont = IMG_LoadTexture(renderer, (basedir + "/bigfont.png").c_str());
  if (bigFont == NULL)
    std::cout << "ACK!  could not big font from " << basedir + "/bigfont.png"
              << " because " << SDL_GetError() << std::endl;
  textFont = IMG_LoadTexture(renderer, (basedir + "/textfont.png").c_str());
  if (textFont == NULL)
    std::cout << "ACK!  could not text font from " << basedir + "/textfont.png"
              << " because " << SDL_GetError() << std::endl;
}

// class destructor
Font::~Font() {
  SDL_DestroyTexture(bigFont);
  SDL_DestroyTexture(textFont);
}

void Font::printTextToSurface(SDL_Renderer *renderer, std::string text,
                              UR_FONT_ENUM whichFont, SDL_Point destPos,
                              SDL_Color textColor) {
  // TODO: the two fonts are of different sizes... defined in ur.h
  for (std::string::size_type i = 0; i < text.size(); ++i) {
    Sint64 ascii = char2ascii(text[i]);

    SDL_Rect sourcePos;
    sourcePos.h = FONT_TEXT_Y;
    sourcePos.w = FONT_TEXT_X;
    sourcePos.x = (ascii - 1) * FONT_TEXT_X;
    sourcePos.y = 0;

    SDL_Rect charDestPos;
    charDestPos.x = destPos.x + i * FONT_TEXT_X;
    charDestPos.y = destPos.y;
    charDestPos.w = FONT_TEXT_X;
    charDestPos.h = FONT_TEXT_Y;

    // Change the colour of the letter to the desired colour before RenderCopy.

    // TODO: this has side-effect of changing color mod on the texture itself,
    // which may be undesirable.
    SDL_SetTextureColorMod(textFont, textColor.r, textColor.g, textColor.b);
    SDL_RenderCopy(renderer, textFont, &sourcePos, &charDestPos);
  }
}

Sint64 Font::char2ascii(char input) { return (Sint64)input; }
} // namespace ur

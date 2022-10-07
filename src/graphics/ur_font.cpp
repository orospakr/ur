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

#include "ur_font.h"		// class's header file

namespace ur {

// class constructor
Font::Font (std::string basedir, SDL_PixelFormat * screenFormat)
{
  // load up the fonts
  SDL_Surface *bigFontLoad, *textFontLoad;

  bigFontLoad = SDL_LoadBMP ((basedir + "/bigfont.bmp").c_str ());
  if (bigFontLoad == NULL)
    std::cout << "ACK!  could not big font from " << basedir +
      "/bigfont.bmp" << std::endl;
  textFontLoad = SDL_LoadBMP ((basedir + "/textfont.bmp").c_str ());
  if (textFontLoad == NULL)
    std::cout << "ACK!  could not text font from " << basedir +
      "/textfont.bmp" << std::endl;
  bigFont = SDL_ConvertSurface (bigFontLoad, screenFormat, SDL_SRCCOLORKEY);
  textFont = SDL_ConvertSurface (textFontLoad, screenFormat, SDL_SRCCOLORKEY);
  //SDL_SetColorKey (bigFont, SDL_SRCCOLORKEY, SDL_MapRGB (screenFormat, 255, 255, 255));
  //SDL_SetColorKey (textFont, SDL_SRCCOLORKEY, SDL_MapRGB (screenFormat, 255, 255, 255));
  SDL_FreeSurface (bigFontLoad);
  SDL_FreeSurface (textFontLoad);
}

// class destructor
Font::~Font ()
{
  SDL_FreeSurface (bigFont);
  SDL_FreeSurface (textFont);
}

void
Font::printTextToSurface (SDL_Surface * surface, std::string text,
			     UR_FONT_ENUM whichFont, SDL_Rect destPos,
			     Sint64 offset, SDL_Color textColor)
{
  // the two fonts are of different sizes... defined in ur.h
  const char *cstrbuf = text.c_str ();
  Sint64 position = offset;
  while (*(cstrbuf + position) != '\0')
    {
      Sint64 result = char2ascii (*(cstrbuf + position));

      
      //std::cout << *(cstrbuf+position);
      //std::cout << " == " << result << std::endl;
      SDL_Rect sourcePos;
      sourcePos.h = FONT_TEXT_Y;
      sourcePos.w = FONT_TEXT_X;
      sourcePos.x = (result - 1) * FONT_TEXT_X;
      sourcePos.y = 0;
      destPos.x += FONT_TEXT_X;

      SDL_Surface * fontBuffer = SDL_CreateRGBSurface(surface->flags,sourcePos.w,sourcePos.h,surface->format->BitsPerPixel,surface->format->Rmask,surface->format->Gmask,surface->format->Bmask,surface->format->Amask);
      SDL_SetColorKey (fontBuffer, SDL_SRCCOLORKEY, SDL_MapRGB (surface->format, 255, 255, 255));

      SDL_BlitSurface (textFont,&sourcePos,fontBuffer,NULL);
      // now that we have the letter sitting in its own temporary surface, we're going to change the colour...
      Uint16 * raw_pixels = (Uint16 *)fontBuffer->pixels;
      //std::cout << "  Source positions are: x=" << sourcePos.x << ", y=" << sourcePos.y;
      //std::cout << "\n  Destination positions are: x=" << destPos.x << ", y=" << destPos.y  << std::endl;
      //std::cout << "  Still good!\n";
      SDL_LockSurface(fontBuffer);
      for (Uint64 hcounter = 0; hcounter<sourcePos.h;hcounter++)
	for (Uint64 wcounter = 0; wcounter<sourcePos.w; wcounter++)
	  {
	    Uint64 offset = (hcounter*FONT_TEXT_X+wcounter);
	    if (SDL_MapRGB(fontBuffer->format,0,0,0)==raw_pixels[offset])
	      {
		//std::cout << " \n Hit at "<< hcounter << ", " << wcounter << std::endl;
		raw_pixels[offset]=SDL_MapRGB(fontBuffer->format,textColor.r,textColor.g,textColor.b);
	      } 
	  }
      SDL_UnlockSurface(fontBuffer);
      SDL_BlitSurface (fontBuffer, NULL, surface, &destPos);
      SDL_FreeSurface (fontBuffer);
      position++;
    }
}

Sint64
Font::char2ascii (char input)
{
  return (Sint64) input;
}
}

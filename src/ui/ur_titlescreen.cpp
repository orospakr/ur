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

#include "ur_titlescreen.h" // class's header file

namespace ur
{

  // class constructor
  Titlescreen::Titlescreen(std::string basedir,
                           SDL_PixelFormat screenFormat, Font *fonts, Audio *audio)
  {
    scrollerText =
        "                                           Welcome to UR!  Greetz out to Sieg, Thoth, OverDrive!";
    audioManager = audio;
    audioManager->pushBGM("sweetdre.xm");
    fontManager = fonts;
    scrollerPos = 0;
    SDL_Surface *titleGraphicLoad;
    titleGraphicLoad = SDL_LoadBMP((basedir + "titlescreen.bmp").c_str());
    if (titleGraphicLoad == NULL)
      std::cout << "!! Unable to load title screen image from " << basedir + "titlescreen.bmp" << std::endl;
    titleGraphic =
        SDL_ConvertSurface(titleGraphicLoad, &screenFormat, SDL_SRCCOLORKEY);
    SDL_FreeSurface(titleGraphicLoad);
    // andrew: this is where you left off at 9 pm Jan 06, 2003
  }

  // class destructort
  Titlescreen::~Titlescreen()
  {
    // insert your code here
  }

  Sint64
  Titlescreen::run(UR_INPUT keystate, SDL_Surface *screen)
  {
    Sint64 result = 1;
    // draw the screen
    SDL_Rect logoPosition;
    logoPosition.x = (SCREEN_WIDTH / 2) - (titleGraphic->w / 2);
    logoPosition.y = (SCREEN_HEIGHT / 2) - (titleGraphic->h / 2);
    logoPosition.w = titleGraphic->w;
    logoPosition.h = titleGraphic->h;
    SDL_BlitSurface(titleGraphic, NULL, screen, &logoPosition);

    // draw welcome text
    std::string welcomeText;
    welcomeText = "Press Start Button!";
    SDL_Rect textPosition;
    textPosition.x =
        (SCREEN_WIDTH / 2) - (FONT_TEXT_X * (welcomeText.length()) / 2);
    textPosition.y = SCREEN_HEIGHT - (FONT_TEXT_Y * 2);
    textPosition.h = FONT_TEXT_Y;
    textPosition.w = FONT_TEXT_X * welcomeText.length();
    SDL_Color textColor;
    textColor.r = audioManager->VUmeterL / 255;
    // std::cout << audioManager->VUmeterL << std::endl;
    textColor.g = 127;
    textColor.b = 127;
    fontManager->printTextToSurface(screen, welcomeText, urFont_Text,
                                    textPosition, 0, textColor);

    // draw scroller
    SDL_Rect scrollerDest;
    scrollerDest.x = 10;
    scrollerDest.y = SCREEN_HEIGHT - 64;
    scrollerDest.h = FONT_TEXT_Y;
    scrollerDest.w = SCREEN_WIDTH;
    scrollerPos = SDL_GetTicks() / 66 % scrollerText.length();

    fontManager->printTextToSurface(screen, scrollerText, urFont_Text,
                                    scrollerDest, scrollerPos, textColor);

    // see if user hit start button
    if (keystate.start)
    {
      audioManager->popBGM();
      result = 0;
    }
    return result;
  }

}

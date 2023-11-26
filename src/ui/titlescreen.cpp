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

#include "ui/titlescreen.h" // class's header file
#include <SDL.h>

namespace ur {

// class constructor
Titlescreen::Titlescreen(std::string basedir, SDL_Renderer *renderer,
                         Font *fonts, Audio *audio) {
    scrollerText = "                                           Welcome to UR!  "
                   "Greetz out to Sieg, Thoth, OverDrive!";
    audioManager = audio;
    audioManager->pushBGM("sweetdre.xm");
    fontManager = fonts;
    SDL_Surface *titleGraphicLoad;
    titleGraphicLoad = SDL_LoadBMP((basedir + "titlescreen.bmp").c_str());
    if (titleGraphicLoad == NULL)
        std::cout << "!! Unable to load title screen image from "
                  << basedir + "titlescreen.bmp" << std::endl;
    titleGraphic = SDL_CreateTextureFromSurface(renderer, titleGraphicLoad);
    SDL_FreeSurface(titleGraphicLoad);
}

// class destructor
Titlescreen::~Titlescreen() {
    // insert your code here
}

Sint64 Titlescreen::run(UR_INPUT keystate, SDL_Renderer *renderer) {
    Sint64 result = 1;
    // draw the screen
    SDL_Rect logoPosition;

    // get size of titlegraphic struct
    int titleGraphicWidth, titleGraphicHeight;
    SDL_QueryTexture(titleGraphic, NULL, NULL, &titleGraphicWidth,
                     &titleGraphicHeight);

    logoPosition.x = (SCREEN_WIDTH / 2) - (titleGraphicWidth / 2);
    logoPosition.y = (SCREEN_HEIGHT / 2) - (titleGraphicHeight / 2);
    logoPosition.w = titleGraphicWidth;
    logoPosition.h = titleGraphicHeight;
    SDL_RenderCopy(renderer, titleGraphic, NULL, &logoPosition);

    // draw welcome text
    std::string welcomeText;
    welcomeText = "Press Start Button!";
    SDL_Point textPosition;
    textPosition.x =
        (SCREEN_WIDTH / 2) - (FONT_TEXT_X * (welcomeText.length()) / 2);
    textPosition.y = SCREEN_HEIGHT - (FONT_TEXT_Y * 2);
    SDL_Color textColor;
    textColor.r = audioManager->VUmeterL / 255;
    // std::cout << audioManager->VUmeterL << std::endl;
    textColor.g = 127;
    textColor.b = 127;
    fontManager->printTextToSurface(renderer, welcomeText, urFont_Text,
                                    textPosition, textColor);

    // marquee width
    Sint64 marqueeWidth = FONT_TEXT_X * scrollerText.length() + SCREEN_WIDTH;
    // draw scroller
    SDL_Point scrollerDest;
    // TODO: using modulo here (to avoid a ticking variable) is basically
    // landing at an arbitrary point in the scroll position, but because
    // SDL_Ticks starts at 0 at app start time, and this scroller is virtually
    // the first thing we do, excepting a bit of a race condition, the scroller
    // mostly lands in its proper stage-left starting position. computing an
    // offset with initial time when Titlescreen is instantiated could solve
    // this.
    scrollerDest.x = ((SDL_GetTicks() / 5) % (marqueeWidth)) * -1;
    scrollerDest.y = SCREEN_HEIGHT - 64;

    fontManager->printTextToSurface(renderer, scrollerText, urFont_Text,
                                    scrollerDest, textColor);

    // see if user hit start button
    if (keystate.start) {
        audioManager->popBGM();
        result = 0;
    }
    return result;
}

} // namespace ur

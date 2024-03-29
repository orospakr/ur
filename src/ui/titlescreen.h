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

#ifndef UR_TITLESCREEN_H
#define UR_TITLESCREEN_H

#include "audio/audio.h"
#include "game/map.h"
#include "graphics/font.h"
#include "ur.h"
#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

namespace ur {

/*
 * The title screen class.
 */
class Titlescreen {
  public:
    // class constructor
    Titlescreen(std::string basedir, SDL_Renderer *renderer, Font *fonts,
                Audio *audio);
    // class destructor
    ~Titlescreen();
    /* runs the Title Screen one cycle.  Returns 0 if the user hit START and the
     *game should begin , otherwise just run it again.
     */
    Sint64 run(UR_INPUT keystate, SDL_Renderer *renderer);

  private:
    SDL_Texture *titleGraphic;
    Font *fontManager;
    std::string scrollerText;
    Audio *audioManager;
};

} // namespace ur

#endif // UR_TITLESCREEN_H

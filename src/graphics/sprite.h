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
 * The graphical manifestation of a urObject.  Contains the
 * animations, and other graphics-specific data
 */

#ifndef UR_SPRITE_H
#define UR_SPRITE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include <iostream>
#include "SDL.h"
#include "ur.h"

#include "graphics/layer.h"

namespace ur {

class Sprite
{
public:
  // class constructor
  Sprite (std::string spriteBMPFilename, SDL_PixelFormat * screenFormat);
  // class destructor
  ~Sprite ();

  /* this is all of the sprite data in a giant SDL_Surface.  Read docs/sprite.txt
   * for more info
   */
  SDL_Surface *spriteData;

  /* the following are funcs that return SDL_Rects that point to the relevant area
   * of the spriteData surface, depending upon the sprite type, and animation status.
   */

  SDL_Rect getPotrait ();
  void advanceAnimation ();
  UR_DIRECTION_ENUM currentDir;
  UR_ANIM_ENUM currentAnim;
  void drawToScreen (SDL_Surface * screen, SDL_Rect screenGeom);

  /* These are updated automatically by the parent Object.  Don't bother
   * changing them from this scope.
   */
  Sint64 xpos, ypos;
private:
  Sint64 animationPhase;
  SDL_Rect *getAnim (UR_DIRECTION_ENUM direction, UR_ANIM_ENUM animType);
};

}

#endif // UR_SPRITE_H

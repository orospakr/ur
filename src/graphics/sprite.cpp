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

#include <SDL_image.h>

#include "graphics/sprite.h" // class's header file

namespace ur {

// class constructor
Sprite::Sprite(std::string spriteBMPFilename, SDL_Renderer *renderer) {
  animationPhase = 0;
  currentDir = urDirNone;
  spriteData = IMG_LoadTexture(renderer, spriteBMPFilename.c_str());
  if (spriteData == NULL) {
    std::cout << "!! Error loading sprite " << spriteBMPFilename << " because "
              << SDL_GetError() << std::endl;
    exit(1);
  }

  // TODO: colourkeys again or alpha?
  // SDL_SetColorKey(spriteData, SDL_SRCCOLORKEY,
  // SDL_MapRGB(screenFormat, 255, 255, 255));
}

// class destructor
Sprite::~Sprite() { SDL_DestroyTexture(spriteData); }

SDL_Rect *Sprite::getAnim(UR_DIRECTION_ENUM direction, UR_ANIM_ENUM animType) {
  SDL_Rect *result = new SDL_Rect;
  result->h = TILE_WIDTH;
  result->w = TILE_HEIGHT;
  switch (animType) {
  case urAnimWalk:
    result->y = 0;
    break;
  case urAnimWait:
    result->y = TILE_HEIGHT * 8; // we want the second set
    break;
  default:
    result->y = 0;
    break;
  }
  switch (direction) {
  case urDirNorth:
    result->y += TILE_HEIGHT * 0;
    break;
  case urDirSouth:
    result->y += TILE_HEIGHT * 1;
    break;
  case urDirEast:
    result->y += TILE_HEIGHT * 2;
    break;
  case urDirWest:
    result->y += TILE_HEIGHT * 3;
    break;
  case urDirNorthEast:
    result->y += TILE_HEIGHT * 4;
    break;
  case urDirNorthWest:
    result->y += TILE_HEIGHT * 5;
    break;
  case urDirSouthEast:
    result->y += TILE_HEIGHT * 6;
    break;
  case urDirSouthWest:
    result->y += TILE_HEIGHT * 7;
    break;
  default:
    result->y += TILE_HEIGHT * 1;
    break;
  }
  result->x = (TILE_WIDTH * 5) + (TILE_WIDTH * animationPhase);
  return result;
}

void Sprite::advanceAnimation() {
  // animation phase should be modulo elapsed time ms, divide by 33 to get 30
  // fps.
  animationPhase = SDL_GetTicks() / 33 / 3 % 8;
}

SDL_Rect Sprite::getPotrait() {
  SDL_Rect result;
  result.w = TILE_WIDTH * 5;
  result.h = TILE_HEIGHT * 8;
  result.x = 0;
  result.y = 0;
  return result;
}

void Sprite::drawToScreen(SDL_Renderer *renderer, SDL_Rect screenGeom) {
  SDL_Rect dstRect;
  dstRect.h = TILE_HEIGHT;
  dstRect.w = TILE_WIDTH;
  dstRect.x = xpos;
  dstRect.y = ypos;
  dstRect.x -= screenGeom.x;
  dstRect.y -= screenGeom.y;
  // dstRect.x=abs(dstRect.x);
  // dstRect.y=abs(dstRect.y);
  SDL_Rect *animResult = getAnim(currentDir, currentAnim);
  SDL_RenderCopy(renderer, spriteData, animResult, &dstRect);
  delete animResult;
}

} // namespace ur
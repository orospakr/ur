/*
    This file is part of Usurper's Redemption.

    Usurper's Redemption is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Usurper's Redemption is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Usurper's Redemption; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef UR_OBJECT_H
#define UR_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "ur.h"
#include "ur_sprite.h"

/*
 * A UR object.  Shows up as a sprite. Things such as
 * characters, badniks, control panels, etc. are sprites.
 * They can also have talkto lines, and props of other types.
 */


class ur_object
{
public:
  /* objectPath contains the base path in which the object files can be found.
   * objectName is the name of the object (there may be more than one with the
   * same name), and is used to determine which directory the data may be loaded
   * from, amongst other things)
   */
  ur_object (std::string objectPath, std::string objectName,
	     SDL_PixelFormat * screenFormat, ur_layer * hostLayer);

  // class destructor
  ~ur_object ();

  void run ();
  Sint64 move (UR_DIRECTION_ENUM key);

  /* The object's area of influence, relative to the whole map */
  UR_INFLUENCE areaInfluence;

  /* graphical manifestation
   */
  ur_sprite *spriteGrafx;

  /* dynamics
   */
  Sint64 xpos;
  Sint64 ypos;
  Sint64 xvel;
  Sint64 yvel;

  /* Object's common name
   */
    std::string name;

  /* object's type */
  UR_OBJTYPE_ENUM type;

  /* object's alignment/faction... good, evil, etc... */
  UR_FACTION_ENUM faction;

  /* a vector of objects to make up the character's
   * inventory.  Not allowed for standard objects... chars only
   */
    std::vector < ur_object > inventory;

  /* a vector of all the speech responses
   */
    std::vector < UR_TALK_DATA > speechData;

  /* *** The following props are the stats.  They don't (normally) need
   * *** to be set unless the object is a character
   */
  /* experience. Can goes as high as you like (within the bounds of Sint64, of course)
   */
  Sint64 exp;
  /* strength setting.  Choose one between 0-100
   */
  Sint64 strength;
  /* constitution.  Choose one between 0-100
   */
  Sint64 constitution;
  /* gender.  male=0, female=1... these values are arbitrary, I may note...
   */
  Sint64 gender;
  /* the max velocities.  Higher for Sonic than others, obviously. ;P
   */
  Sint64 velmax;

  /* This draws the object to the supplied surface.  Note that it just shafts
   * the job down to its sprite object.
   */
  void drawToScreen (SDL_Surface * screen, SDL_Rect screenGeom);

  /* AI driver props
   */
  bool AI_moveMe;

  bool dead;


  /// collision detection method.  NOTE:  When objects collide, the object that 'affects'
  /// the action should be the one that makes the calls to the affect_xxx series methods
  /// on the target object
  Sint64 collision (ur_object * otherEntity);

  Sint64 affect_instaKill ();
  Sint64 affect_injure (Sint64 hitPoints);
  Sint64 affect_push (UR_DIRECTION_ENUM sourceDirection);

private:
    ur_layer * bossLayer;

};

#endif // UR_OBJECT_H

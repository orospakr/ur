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

#include "game/object.h" // class's header file

namespace ur {
std::string charToSTLString(char *input) {
    std::string blah(input);
    return blah;
}

// class constructor
Object::Object(std::string objectPath, std::string objectName,
               SDL_Renderer *renderer, ObjectOwner *owner) {
    xpos = 0;
    ypos = 0;
    areaInfluence.w = TILE_WIDTH;
    areaInfluence.h = TILE_HEIGHT;
    areaInfluence.x = xpos;
    areaInfluence.y = ypos;
    this->owner = owner;
    dead = false;
    char *loadBuffer = new char[2048];
    name = objectName;
    faction = urFact_BadNik;
    xvel = 0;
    yvel = 0;

    /* This iostream object is used to load up the object's settings
     */
    std::ifstream loadReader;
    spriteGrafx =
        new Sprite(objectPath + objectName + "/sprites.png", renderer);
    loadReader.open((objectPath + objectName + "/def.txt").c_str(),
                    std::ifstream::in);
    if (!loadReader.good()) {
        printf("!! Unable to open object definition file.\n");
        exit(1); // call system to stop
    }

    /* load up the object's stats, delimited by newlines in the def.txt file */
    loadReader.getline(loadBuffer, 100);
    gender = atoi(loadBuffer);

    loadReader.getline(loadBuffer, 100);
    exp = atoi(loadBuffer);

    loadReader.getline(loadBuffer, 100);
    strength = atoi(loadBuffer);

    loadReader.getline(loadBuffer, 100);
    constitution = atoi(loadBuffer);

    loadReader.getline(loadBuffer, 100);
    velmax = atoi(loadBuffer);

    /* Now, to load up the speech responses... this goes until the end of the
     * file
     */
    // std::cout << "Loading speech data structures...\n";
    while (!loadReader.eof()) {
        UR_TALK_DATA tempSpeechLoad;
        loadReader.getline(loadBuffer, 2048);
        tempSpeechLoad.prompt = charToSTLString(loadBuffer);
        loadReader.getline(loadBuffer, 2048);
        tempSpeechLoad.response = charToSTLString(loadBuffer);
        speechData.push_back(tempSpeechLoad);
        // std::cout << "Succeeded loading one speech data structure.\n";
    }
    delete[] loadBuffer;
    loadReader.close();

    this->owner->registerObject(this);
}

// class destructor
Object::~Object() { delete spriteGrafx; }

void Object::run() {
    // this method needs to take run every frame, and take into account time
    // elapsed since last frame

    spriteGrafx->currentAnim = urAnimWalk; // this bit should change

    /* update the sprite's own position props
     */
    spriteGrafx->xpos = xpos;
    spriteGrafx->ypos = ypos;
    spriteGrafx->advanceAnimation();
    /* now let's set our area of influence... and if we're dead, we're gonna set
     * it to nothing, since dead things can't do much... this can be replaced
     * with more elaborate code for funky objects...
     */

    areaInfluence.w = TILE_WIDTH;
    areaInfluence.h = TILE_HEIGHT;
    areaInfluence.x = xpos;
    areaInfluence.y = ypos;

    if (dead) {
        areaInfluence.h = 0;
        areaInfluence.w = 0;
        areaInfluence.x = 0;
        areaInfluence.y = 0;
    }
}

Sint64 Object::move(UR_DIRECTION_ENUM key) {
    if (dead)
        return 1; // if we're dead we're not moving anymore. :)
    switch (key) {
    case urDirNorth:
        yvel--;
        if ((yvel * (-1)) >= velmax)
            yvel = (velmax * (-1));
        if (xvel < 0)
            xvel++;
        if (xvel > 0)
            xvel--;
        break;
    case urDirSouth:
        yvel++;
        if (yvel >= velmax)
            yvel = velmax;
        if (xvel < 0)
            xvel++;
        if (xvel > 0)
            xvel--;
        break;
    case urDirWest:
        xvel--;
        if ((xvel * (-1)) >= velmax)
            xvel = (velmax * (-1));
        if (yvel < 0)
            yvel++;
        if (yvel > 0)
            yvel--;
        break;
    case urDirEast:
        xvel++;
        if (xvel >= velmax)
            xvel = velmax;
        if (yvel < 0)
            yvel++;
        if (yvel > 0)
            yvel--;
        break;
    case urDirNorthWest:
        yvel--;
        if ((yvel * (-1)) >= velmax)
            yvel = (velmax * (-1));
        xvel--;
        if ((xvel * (-1)) >= velmax)
            xvel = (velmax * (-1));
        break;
    case urDirNorthEast:
        yvel--;
        if ((yvel * (-1)) >= velmax)
            yvel = (velmax * (-1));
        xvel++;
        if (xvel >= velmax)
            xvel = velmax;
        break;
    case urDirSouthWest:
        yvel++;
        if (yvel >= velmax)
            yvel = velmax;
        xvel--;
        if ((xvel * (-1)) >= velmax)
            xvel = (velmax * (-1));
        break;
    case urDirSouthEast:
        yvel++;
        if (yvel >= velmax)
            yvel = velmax;
        xvel++;
        if (xvel >= velmax)
            xvel = velmax;
        break;
    default:
        /* decay velocity
         */
        if (yvel < 0)
            yvel++;
        if (yvel > 0)
            yvel--;
        if (xvel < 0)
            xvel++;
        if (xvel > 0)
            xvel--;
        break;
    }

    // TODO: aha, velocity/physics calculation below should be done on every
    // run() tick, not in key handler. Key handler
    //   should set a state of a key command to be handled in run tick. This
    //   could be causing issues with velocity decay?

    Sint64 futureX =
        xpos + xvel; // values that could be... but only if the APM permits it!
    Sint64 futureY = ypos + yvel;

    Vector2D velocity(static_cast<float>(xvel) / TILE_WIDTH,
                      static_cast<float>(yvel) / TILE_HEIGHT);

    Point2D position(static_cast<float>(xpos) / TILE_WIDTH,
                     static_cast<float>(ypos) / TILE_HEIGHT);

    auto mapCollision =
        this->owner->checkMapPathCollision(this, position, velocity);

    // TODO: handle new clamped collision result here.

    //    if (mapCollision.collision) {
    //        // adopt the collision position as our new position.
    //        xpos = mapCollision.x;
    //        ypos = mapCollision.y;
    //        // set velocities to zero, dead stop.
    //        xvel = 0;
    //        yvel = 0;
    //        // TODO: should only zero out the velocity on the axis that caused
    //        the collision.
    //    } else {
    //        xpos = futureX;
    //        ypos = futureY;
    //    }

    /* Now, we need to check to ensure we have not gone outside the bounds of
     * the map
     */
    // x axis
    if (xpos < 0) // left-bound
    {
        xvel = 0;
        xpos = 0;
    }
    if (xpos > (MAP_WIDTH * TILE_WIDTH)) // right-bound
    {
        xvel = 0; // we've gone bump against the edge of the map, so full stop
                  // on this axis
        xpos = (MAP_WIDTH * TILE_WIDTH);
    }

    // y axis
    if (ypos < 0) // upper-bound
    {
        yvel = 0; // we've gone bump against the edge of the map, so full stop
                  // on this axis
        ypos = 0;
    }
    if (ypos > (MAP_HEIGHT * TILE_HEIGHT)) // lower-bound
    {
        yvel = 0;
        ypos = (MAP_HEIGHT * TILE_HEIGHT);
    }

    // update the sprite's direction with the keypress
    spriteGrafx->currentDir = key;

    // TODO: restore object collision detection

    //  // all that done, we now need to check for object collisions...
    //  for (Sint64 counter = 0; counter < MAX_OBJS; counter++) {
    //    if (hostLayer->objects[counter] == this)
    //      continue; // I don't want to bother with this one... it's me!
    //    if (hostLayer
    //            ->objects[counter]) // do the following if this object is not
    //            NULL
    //    {
    //      // std::cout << "Object #" << counter << " was not null.\n";
    //      bool xInRange = false;
    //      bool yInRange = false;
    //
    //      Sint64 xNearBound = hostLayer->objects[counter]->areaInfluence.x;
    //      Sint64 xFarBound =
    //          xNearBound + hostLayer->objects[counter]->areaInfluence.w;
    //      // std::cout << xNearBound << std::endl;
    //      // std::cout << xFarBound << std::endl;
    //
    //      // std::cout << bossLayer->objects[counter]->areaInfluence.x <<
    //      std::endl;
    //
    //      Sint64 yNearBound = hostLayer->objects[counter]->areaInfluence.y;
    //      Sint64 yFarBound =
    //          yNearBound + hostLayer->objects[counter]->areaInfluence.h;
    //
    //      if ((xpos > xNearBound) && (xpos < xFarBound)) {
    //        xInRange = true;
    //        // std::cout << "X was in range for something!\n";
    //      }
    //      if ((ypos > yNearBound) && (ypos < yFarBound)) {
    //        yInRange = true;
    //        // std::cout << "Y was in range for something!\n";
    //      }
    //
    //      if (xInRange && yInRange) {
    //        std::cout << "We've hit some shiziat!!\n";
    //        dead = true;
    //        collision(hostLayer->objects[counter]);
    //      }
    //      // we've hit something!!
    //    }
    //  }
    return 0;
}

Sint64 Object::collision(Object *otherEntity) {
    // we've hit something!  Let's see if we should do anything to that
    // something...

    /* this contains just a simple little 'program' that makes the object
     * tell whether it is a 'good guy' or 'bad guy', and if it's a 'bad guy',
     * tries to injure a 'good guy' if it collides with us
     */
    if ((faction == urFact_BadNik) &&
        (otherEntity->faction ==
         urFact_FF)) // if I'm a badnik and you're an FF...
    {
        // quick and easy means of death... ;)
        otherEntity->affect_instaKill();
    }
    if (faction == urFact_FF) {
        // do nothing... yet.  You nuke badniks by shooting at them and other
        // such things
    }
    return 0;
}

Sint64 Object::affect_instaKill() {
    dead = true;
    return 0;
}

Sint64 Object::affect_injure(Sint64 hitPoints) {
    // weenis
    return 0;
}
Sint64 Object::affect_push(UR_DIRECTION_ENUM sourceDirection) {
    // weenis
    return 0;
}

void Object::drawToScreen(SDL_Renderer *renderer, SDL_Rect screenGeom) {

    spriteGrafx->drawToScreen(renderer, screenGeom);
}

} // namespace ur

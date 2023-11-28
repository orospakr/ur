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
    areaInfluence.w = TILE_WIDTH;
    areaInfluence.h = TILE_HEIGHT;
    areaInfluence.x = static_cast<int>(position.x * TILE_WIDTH);
    areaInfluence.y = static_cast<int>(position.y * TILE_HEIGHT);
    this->owner = owner;
    dead = false;
    char *loadBuffer = new char[2048];
    name = objectName;
    faction = urFact_BadNik;

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
    // first, run physics using currentdir
    if (dead) {
        // if we're dead we're not moving anymore. :)
        velocity = Vector2D();
        return;
    }

    // fractional value to incrase velocity by when key is pressed.
    const double accel = 0.05;

    const double velmax = 0.2;

    switch (this->directionInput) {
        case urDirNorth:
            velocity.y += -accel;

            // clamp vertical velocity to velmax:
            if (velocity.y < -velmax) {
                velocity.y = -velmax;
            }

            // decay horizontal velocity:
            if (abs(velocity.x) < accel) {
                velocity.x = 0;
            } else if (velocity.x < 0) {
                velocity.x += accel;
            } else if (velocity.x > 0) {
                velocity.x -= accel;
            }

            break;
        case urDirSouth:
            velocity.y += accel;

            // clamp vertical velocity to velmax:
            if (velocity.y > velmax) {
                velocity.y = velmax;
            }

            // decay horizontal velocity:
            if (abs(velocity.x) < accel) {
                velocity.x = 0;
            } else if (velocity.x < 0) {
                velocity.x += accel;
            } else if (velocity.x > 0) {
                velocity.x -= accel;
            }
            break;
        case urDirWest:
            velocity.x += -accel;

            // clamp horizontal velocity to velmax:
            if (velocity.x < -velmax) {
                velocity.x = -velmax;
            }

            // decay vertical velocity:
            if (abs(velocity.y) < accel) {
                velocity.y = 0;
            } else if (velocity.y < 0) {
                velocity.y += accel;
            } else if (velocity.y > 0) {
                velocity.y -= accel;
            }
            break;
        case urDirEast:
            velocity.x += accel;

            // clamp horizontal velocity to velmax:
            if (velocity.x > velmax) {
                velocity.x = velmax;
            }

            // decay vertical velocity:
            if (abs(velocity.y) < accel) {
                velocity.y = 0;
            } else if (velocity.y < 0) {
                velocity.y += accel;
            } else if (velocity.y > 0) {
                velocity.y -= accel;
            }
            break;
        case urDirNorthWest:
            velocity.y += -accel;
            velocity.x += -accel;

            // clamp vertical velocity to velmax:
            if (velocity.y < -velmax) {
                velocity.y = -velmax;
            }

            // clamp horizontal velocity to velmax:
            if (velocity.x < -velmax) {
                velocity.x = -velmax;
            }
            break;

        case urDirNorthEast:
            velocity.y += -accel;
            velocity.x += accel;

            // clamp vertical velocity to velmax:
            if (velocity.y < -velmax) {
                velocity.y = -velmax;
            }

            // clamp horizontal velocity to velmax:
            if (velocity.x > velmax) {
                velocity.x = velmax;
            }
            break;

        case urDirSouthWest:
            velocity.y += accel;
            velocity.x += -accel;

            // clamp vertical velocity to velmax:
            if (velocity.y > velmax) {
                velocity.y = velmax;
            }

            // clamp horizontal velocity to velmax:
            if (velocity.x < -velmax) {
                velocity.x = -velmax;
            }
            break;

        case urDirSouthEast:
            velocity.y += accel;
            velocity.x += accel;

            // clamp vertical velocity to velmax:
            if (velocity.y > velmax) {
                velocity.y = velmax;
            }

            // clamp horizontal velocity to velmax:
            if (velocity.x > velmax) {
                velocity.x = velmax;
            }
            break;

        default:
            // decay velocity:
            if (abs(velocity.x) < accel) {
                velocity.x = 0;
            } else if (velocity.x < 0) {
                velocity.x += accel;
            } else if (velocity.x > 0) {
                velocity.x -= accel;
            }

            if (abs(velocity.y) < accel) {
                    velocity.y = 0;
            } else if (velocity.y < 0) {
                    velocity.y += accel;
            } else if (velocity.y > 0) {
                    velocity.y -= accel;
            }
            break;
    }


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

    // clamp position (and velocity) to map bounds:
    if (position.x < 0) {
        position.x = 0;
        velocity.x = 0;
    } else if (position.x > MAP_WIDTH - 1) {
        position.x = MAP_WIDTH - 1;
        velocity.x = 0;
    }

    if (position.y < 0) {
        position.y = 0;
        velocity.y = 0;
    } else if (position.y > MAP_HEIGHT - 1) {
        position.y = MAP_HEIGHT - 1;
        velocity.y = 0;
    }

//    auto mapCollision =
//            this->owner->checkMapPathCollision(this, position, velocity);

    // TODO: use map collision result, for now just apply velocity:
    position = position + velocity;

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



    // this method needs to take run every frame, and take into account time
    // elapsed since last frame

    spriteGrafx->currentAnim = urAnimWalk; // this bit should change

    /* update the sprite's own position props
     */
    spriteGrafx->xpos = static_cast<int>(position.x * TILE_WIDTH);
    spriteGrafx->ypos = static_cast<int>(position.y * TILE_HEIGHT);
    spriteGrafx->advanceAnimation();
    /* now let's set our area of influence... and if we're dead, we're gonna set
     * it to nothing, since dead things can't do much... this can be replaced
     * with more elaborate code for funky objects...
     */

    areaInfluence.w = TILE_WIDTH;
    areaInfluence.h = TILE_HEIGHT;

    areaInfluence.x = static_cast<int>(position.x * TILE_WIDTH);
    areaInfluence.y = static_cast<int>(position.y * TILE_HEIGHT);

    if (dead) {
        areaInfluence.h = 0;
        areaInfluence.w = 0;
        areaInfluence.x = 0;
        areaInfluence.y = 0;
    }
}

Sint64 Object::move(UR_DIRECTION_ENUM key) {
    this->directionInput = key;

    // update the sprite's direction with the keypress
    spriteGrafx->currentDir = key;

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

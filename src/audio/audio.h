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
#ifndef UR_AUDIO_H
#define UR_AUDIO_H

#include "ur.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <vector>

// include openmpt header
#include "libopenmpt/libopenmpt.hpp"

namespace ur {

class Audio {
  public:
    /**
     * @brief Construct the audio manager. Note will block synchronously as it
     * loads all content.
     *
     */
    Audio();
    void audio_callback(Uint8 *stream, int len);

    void pushBGM(std::string name);
    void popBGM();

    Uint16 VUmeterL;
    Uint16 VUmeterR;

    ~Audio();

  private:
    void load_music(std::string name);
    void unload_music();
    void change_music(std::string name);
    SDL_AudioSpec *obtained_audio_spec;

    // a map of filenames to loaded openmpt modules
    std::map<std::string, openmpt::module *> modules;

    std::string *BGMstack;

    Uint8 BGMstack_ptr;

    // codec specific variables

    // a loaded openmpt module
    openmpt::module *currentMOD;
};
} // namespace ur

#endif // UR_AUDIO_H
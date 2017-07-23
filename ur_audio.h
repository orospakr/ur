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
#ifndef UR_AUDIO_H
#define UR_AUDIO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "ur.h"
#include "libmodplug/modplug.h"

class ur_audio
{
 public:
  ur_audio();
  void audio_callback(Uint8 *stream, int len);

  void pushBGM(std::string name);
  void popBGM();

  Uint16 VUmeterL;
  Uint16 VUmeterR;

  void runAudio();

  ~ur_audio();
 private:
  void load_music(std::string name);
  void unload_music();
  SDL_AudioSpec * obtained_audio_spec;

  std::string * BGMstack;

  Uint8 BGMstack_ptr;

  // currently loaded song file
  char *  loadedBGM;
  // size of currently loaded song file
  Uint64 BGMsize;

  // codec specific variables
  ModPlugFile * currentMOD;
  
  

};

#endif // UR_AUDIO_H

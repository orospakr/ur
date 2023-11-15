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

#include "audio/audio.h" // class's header file

namespace ur {
extern "C" void extern_audio_callback(void *userdata, Uint8 *stream, int len) {
  static_cast<Audio *>(userdata)->audio_callback(stream, len);
}

// private constant vector of module names
const std::vector<std::string> MODULE_NAMES = {"sweetdre.xm", "7thheaven.mod"};

Audio::Audio()
    : VUmeterL{0}, VUmeterR{0}, obtained_audio_spec{new SDL_AudioSpec},
      modules{}, BGMstack{new std::string[10]}, BGMstack_ptr{0},
      currentMOD{NULL} {
  // first load all the modules
  for (auto &name : MODULE_NAMES) {
    load_music(name);
  }

  /* Open the audio device */
  SDL_AudioSpec *desired;

  /* Allocate a desired SDL_AudioSpec */
  desired = new SDL_AudioSpec;

  desired->freq = 44100;

  /* 16-bit little-endian audio */
  desired->format = AUDIO_S16LSB;

  /* set number of channels */
  desired->channels = 2;

  /* Large audio buffer reduces risk of dropouts but increases response time */
  desired->samples = 512;

  /* Our callback function */
  desired->callback = extern_audio_callback;

  /* we're doing something a little weird here:  SDL (being a C library) doesn't
     like the callback being a member of a c++ object, so, I have made a little
     c-like routine that SDL will call. Namely, ur_SDL_audioCallback.  Now, SDL
     does us a favour and lets us pass SDL a little bit of data to pass to the
     callback whenever SDL calls it.  So, it will be a pointer to this object
     and the little c-ish callback routine will be able to fone home.
  */
  desired->userdata = this;

  /* Open the audio device */
  int audioInitResult = SDL_OpenAudio(desired, obtained_audio_spec);
  if (audioInitResult < 0) {
    std::cout << "!! Couldn't open audio!\n";
    std::cout << "   SDL gave error code: " << audioInitResult << std::endl;
    std::cout << SDL_GetError();
  }

  /* desired spec is no longer needed*/
  delete desired;

  SDL_PauseAudio(0);
}

/* callback function... */

void Audio::audio_callback(Uint8 *stream, int len) {
  Sint16 *samples = (Sint16 *)stream;

  // Uint16 highestL = 0;
  // Uint16 highestR = 0;

  if (currentMOD) {
    currentMOD->read_interleaved_stereo(44100, len / 4, (int16_t *)samples);
  }
}

void Audio::pushBGM(std::string name) {
  SDL_LockAudio();
  BGMstack_ptr++;
  BGMstack[BGMstack_ptr] = name;
  change_music(BGMstack[BGMstack_ptr]);
  SDL_UnlockAudio();
}

void Audio::popBGM() {
  SDL_LockAudio();
  if (BGMstack_ptr > 0) {
    unload_music();
    BGMstack_ptr--;
  }
  if (!BGMstack->empty()) {
    change_music(BGMstack[BGMstack_ptr]);
  }
  SDL_UnlockAudio();
}

void Audio::change_music(std::string name) {
  openmpt::module *newMOD = modules[name];
  if (!newMOD) {
    std::cout << "!! Error:  Could not find module " << name << std::endl;
    return;
  }
  SDL_LockAudio();
  currentMOD = newMOD;
  SDL_UnlockAudio();
}

void Audio::load_music(std::string name) {
  std::ifstream loadReader;
  std::string filename = "data/music/" + name;
  struct stat results;
  openmpt::module *loadedModule;

  if (stat(filename.c_str(), &results)) {
    std::cout << std::endl << "!! Could not stat " << filename << std::endl;
    return;
  }

  loadReader.open(filename.c_str(), std::ifstream::in | std::ifstream::binary);
  if (!loadReader.good()) {
    std::cout << std::endl << "!! Unable to load " << name << ". :( \n";
    return;
  }

  // load openpt module:
  try {
    loadedModule = new openmpt::module(loadReader);
  } catch (const std::exception &e) {
    std::cout << "!! Error loading " << name << ": " << e.what() << std::endl;
    return;
  }

  if (!loadedModule) {
    std::cout << std::endl
              << "!! Could not music module " << filename << std::endl;
    return;
  }

  modules[name] = loadedModule;
}

void Audio::unload_music() {
  // TODO
}

Audio::~Audio() {
  SDL_LockAudio();
  delete obtained_audio_spec;
  delete[] BGMstack;
}

} // namespace ur
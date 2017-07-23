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

#include "ur_audio.h"		// class's header file

extern "C" void extern_audio_callback (void * userdata, Uint8 * stream, int len)
{
  static_cast<ur_audio*>(userdata)->audio_callback( stream, len );
}

ur_audio::ur_audio()
{
  obtained_audio_spec = new SDL_AudioSpec;

  currentMOD = NULL;
  BGMstack_ptr = 0;

  BGMstack = new std::string[10];

  /* Open the audio device */
  SDL_AudioSpec *desired;

  /* Allocate a desired SDL_AudioSpec */
  desired = new SDL_AudioSpec;

  /* 22050 Hz - FM Radio Quality */
  desired->freq=44100;
  
  /* 16-bit little-endian audio */
  desired->format=AUDIO_S16LSB;

  /* set number of channels */
  desired->channels=2;
  
  /* Large audio buffer reduces risk of dropouts but increases response time */

  desired->samples=512;
  
  /* Our callback function */
  desired->callback=extern_audio_callback;

  /* we're doing something a little weird here:  SDL (being a C library) doesn't like the
     callback being a member of a c++ object, so, I have made a little c-like routine that SDL will call.
     Namely, ur_SDL_audioCallback.  Now, SDL does us a favour and lets us pass SDL a little bit of data to
     pass to the callback whenever SDL calls it.  So, it will be a pointer to this object and the little c-ish
     callback routine will be able to fone home.
  */
  desired->userdata=this;


  /* Open the audio device */
  int audioInitResult = SDL_OpenAudio(desired,obtained_audio_spec);
  if (audioInitResult <0)
  {
    cout << "!! Couldn't open audio!\n";
    cout << "   SDL gave error code: " << audioInitResult << endl;
    cout << SDL_GetError();
  }

  /* desired spec is no longer needed*/
  delete desired;

  SDL_PauseAudio(0);
}

/* callback function... */
        
void ur_audio::audio_callback (Uint8 *stream, int len) 
{
  Sint16* samples = (Sint16*) stream;

  //Uint16 highestL = 0;
  //Uint16 highestR = 0;

  if (currentMOD) 
    {
      ModPlug_Read(currentMOD,stream,len);
    }

}

void ur_audio::pushBGM(std::string name)
{
  SDL_LockAudio();
  if (BGMstack_ptr > 0)
    unload_music();
  BGMstack_ptr++;
  BGMstack[BGMstack_ptr]=name;
  load_music(BGMstack[BGMstack_ptr]);
  SDL_UnlockAudio();
}

void ur_audio::popBGM()
{
  SDL_LockAudio();
  if (BGMstack_ptr>0)
    {
      unload_music();
      BGMstack_ptr--;
    }
  load_music(BGMstack[BGMstack_ptr]);
  SDL_UnlockAudio();
}

void ur_audio::runAudio()
{
  
}

void ur_audio::load_music(std::string name)
{
  std::ifstream loadReader;
  std::string filename = "data/music/" + name;
  struct stat results;
  if (stat(filename.c_str(), &results))
    {
      cout << endl << "!! Could not stat " << filename << endl;
      return;
    }
  BGMsize = results.st_size;
  loadReader.open( filename.c_str() ,std::ifstream::in | std::ifstream::binary);
  if (!loadReader.good ())
    {
      cout << endl << "!! Unable to load " << name << ". :( \n";
      return;
    }
  loadedBGM = new char[BGMsize];
  loadReader.read(loadedBGM,BGMsize);
  loadReader.close();
  currentMOD=ModPlug_Load(loadedBGM,BGMsize);
}

void ur_audio::unload_music()
{
  ModPlug_Unload(currentMOD);
  delete [] loadedBGM;
}

ur_audio::~ur_audio()
{
  SDL_LockAudio();
  delete [] loadedBGM;
  delete obtained_audio_spec;
  delete [] BGMstack;
}



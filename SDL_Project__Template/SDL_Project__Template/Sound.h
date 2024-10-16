#pragma once
#ifndef _SOUND_H_
#define _SOUND_H_

#include "Game.h"
#include <SDL_mixer.h>

class Sound
{
public:
	//constructors & Deconstructors
	Sound();
	~Sound();
	 
	void PlaySound();
	void LoadSound(std::string _soundFile);


private:
	Mix_Chunk* SoundChunk;
};


#endif // !_SOUND_H_



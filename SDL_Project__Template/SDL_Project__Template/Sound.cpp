#include "Sound.h"

Sound::Sound()
{
	SoundChunk = NULL;
	Mix_Init(MIX_INIT_MP3);//allows for mp3 files to be used
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 6, 4096);
}

Sound::~Sound()
{
	Mix_FreeChunk(SoundChunk);//frees up the sound chunk
	Mix_CloseAudio();//closes audio
}

void Sound::PlaySound()
{
	Mix_PlayChannel(-1, SoundChunk, 0);//plays the file thats stored in SoundChunk at an automatically allocated channel with no repeats
}

void Sound::LoadSound(std::string _soundFile)
{
	SoundChunk = Mix_LoadWAV(_soundFile.c_str());//takes input from function and tries to load that file
	if (!SoundChunk)
	{
		std::cout << Mix_GetError();
	}
}
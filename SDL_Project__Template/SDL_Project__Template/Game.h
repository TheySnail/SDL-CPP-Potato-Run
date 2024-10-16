#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include <SDL.h>
#include "GameObject.h"
#include "SpriteScroll.h"
#include <SDL.h>
#include <iostream>
#include <string>
#include "player.h"
#include "Obstacle.h"
#include "VectorFunctions.h"
#include <cstdlib>
#include "Score.h"
#include "Button.h"

#include "Sound.h"

#include <SDL_ttf.h>
#include <SDL_mixer.h>


class Game
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* image;
	SDL_Texture* texture;

	int Initalise();

	int GameLoop(SDL_Renderer* renderer, TTF_Font* _font, int &_HighScore);

public:
	//constructors & Deconstructors
	Game();
	~Game();

	int FrameRateCount;
};

#endif // !_GAME_H_

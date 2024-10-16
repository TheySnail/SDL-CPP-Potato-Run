#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_

#include"Game.h"


//function prototypes for score

void initScoreTxt(SDL_Renderer* _renderer, std::vector <SDL_Texture*> &_txtVect);


void displayScore(SDL_Renderer* _renderer, std::vector <SDL_Texture*>& _txtVect, int _score);


void displayHighScore(SDL_Renderer* _renderer, std::vector <SDL_Texture*>& _txtVect, int _score, int _x, int _y);

#endif
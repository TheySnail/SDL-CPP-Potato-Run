#pragma once
#ifndef _VECTOR_FUNC_H_
#define _VECOTR_FUNC_H_

#include "Game.h"
#include <SDL.h>
#include <vector>

//function prototypes for obstacle vector functions

void CreateVectOfObstacles(SDL_Renderer* _renderer, std::vector<Obstacle*> &_ObstacleVect, int _speed);

void MoveVectObstacle(std::vector<Obstacle*> &_ObstacleVect);

#endif // !_VECTOR_FUNC_H_

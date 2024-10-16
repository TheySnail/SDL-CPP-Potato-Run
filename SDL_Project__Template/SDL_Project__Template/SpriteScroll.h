#pragma once
#ifndef _SPRITESCROLL_H_
#define _SPRITESCROLL_H_

#include "GameObject.h"
#include <string>

class GameObject;

class SpriteScroll
{
public:
	//constructors & deconstructors
	SpriteScroll(SDL_Renderer* _Renderer, const std::string _imgFile, int _x, int _y, int _w, int _h, int _speed);
	~SpriteScroll();

	void ScrollLeft();
	void DrawScrollToScreen();

	void UpdateSpeed(int _speed);

private:
	int ScrollSpeed;
	int x;
	int y;
	int width;
	GameObject* Image;//trying to create pointer to GameObject 
};

#endif // !_SPRITESCROLL_H_

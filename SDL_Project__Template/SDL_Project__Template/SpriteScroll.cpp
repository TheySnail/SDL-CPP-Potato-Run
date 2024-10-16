#include "SpriteScroll.h"
#include <iostream>

//constuctor
SpriteScroll::SpriteScroll(SDL_Renderer* _Renderer, const std::string _imgFile,int _x,int _y, int _w, int _h, int _speed)
{
	ScrollSpeed = _speed;
	x = _x;
	y = _y;
	width = _w;

	Image = new GameObject(_Renderer, _imgFile, x, y, _w, _h);//trying to create a GameObject object and assign it to pointer
}

SpriteScroll::~SpriteScroll()
{
	delete Image;
}

void SpriteScroll::ScrollLeft()
{
	x = x - ScrollSpeed;//x position = current x minus the scroll spee

	if (x < -width)//if the x is less than the width it resets back to off the screen to the right
		x += width;
}

void SpriteScroll::DrawScrollToScreen()
{
	Image->SetX(x);//updates the first image's x coordinate
	Image->SpriteDrawToScreen();//draws first to screen

	Image->SetX(x+width);//updates the second images coordinate
	Image->SpriteDrawToScreen();//draws second to screen
}

void SpriteScroll::UpdateSpeed(int _speed)
{
	ScrollSpeed = _speed;//updates speed when called
}
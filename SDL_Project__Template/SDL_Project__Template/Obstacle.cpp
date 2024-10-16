#include "Obstacle.h"

#include <iostream>

//constructor
Obstacle::Obstacle(bool _offScreen, bool _isFlying, SDL_Renderer* _Renderer, const std::string _imgFile, int _x, int _y, int _w, int _h,int _speed) :GameObject(_Renderer, _imgFile, _x, _y, _w, _h)
{
	offScreen = _offScreen;
	isFlying = _isFlying;
	MovementSpeed = _speed;
	x = _x;
	y = _x;

}

Obstacle::~Obstacle()
{

}

//acts as a second destructor almost allowing me to reuse the same object just resetting all the variables 
void Obstacle::RepopulateObject(bool _offScreen, bool _isFlying, int _x, int _y, int _w, int _h, int _speed)
{
	offScreen = _offScreen;
	isFlying = _isFlying;
	MovementSpeed = _speed;
	this->SetX(_x);
	this->SetY(_y);
	x = _x;
	y = _y;

	this->setH(_h);
	this->setW(_w);
}

void Obstacle::ObjectScrollLeft()
{
	x = x - MovementSpeed;//takes current x position subtracts movement speed 
	this->SetX(x);//updates x position

	if (x < 0 - GetW())//if the x is less than 0 minus the width of the object it is completely off screen meaning it can be reintitalized and created into a new obstacle
	{
		offScreen = true;
	}
}

void Obstacle::DrawObjectToScreen()
{
	this->SpriteDrawToScreen();
}


void Obstacle::UpdateSprite()
{
	if (isFlying == true)//sets it to the flying sprite
	{

		SDL_Surface* image = SDL_LoadBMP("Sprites/birdF1.bmp");//creates surface from file specified


		texImage = SDL_CreateTextureFromSurface(Renderer, image);
		SDL_FreeSurface(image);//frees up surface space	
	}
	else
	{
		SDL_Surface* image = SDL_LoadBMP("Sprites/fork.bmp");//creates surface from file specified


		texImage = SDL_CreateTextureFromSurface(Renderer, image);
		SDL_FreeSurface(image);//frees up surface space	
	}
}

void Obstacle::increaseSpeed(int _speed)//allows speed to be increased if object already exists
{
	MovementSpeed = _speed;
}
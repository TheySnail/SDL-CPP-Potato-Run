#include "player.h"
#include <SDL.h>

#include <iostream>

player::player(bool _isDead, SDL_Renderer* _Renderer, const std::string _imgFile, int _x, int _y, int _w, int _h) : GameObject(_Renderer, _imgFile, _x, _y, _w, _h)
{
	isDead = _isDead;
	isJumping = false;
	SpriteNum = 0;
	RotateVal = 0;

}

player::~player()
{

}


void player::PlayerJump()
{
	position.y -= 15;
}

void player::PlayerFall()
{
	position.y += 15;
}

void player::SpriteDrawToScreen()
{
	/*SDL_RenderDrawRect(Renderer, &position);*/
	SDL_RenderCopyEx(this->Renderer, this->texImage, 0, &position, RotateVal ,0, SDL_FLIP_NONE);
}

void player::UpdateSprite(int _spriteNum)
{
	int s = _spriteNum % 2;//as animation is only 2 frames it works out if it should be the 90 degree sprite or 45 by modulus 2 which means when sprite num is even  itll be 0 and when it is odd if will be 1

	if (s == 0)
	{
		SDL_Surface* image = SDL_LoadBMP("Sprites/PotatoF1.bmp");//creates surface from file specified

		if (texImage != nullptr)
		{
			SDL_DestroyTexture(texImage);
		}

		texImage = SDL_CreateTextureFromSurface(Renderer, image);
		SDL_FreeSurface(image);//frees up surface space	
	}

	if (s == 1)
	{
		SDL_Surface* image = SDL_LoadBMP("Sprites/PotatoF2.bmp");//creates surface from file specified

		if (texImage != nullptr)
		{
			SDL_DestroyTexture(texImage);
		}

		texImage = SDL_CreateTextureFromSurface(Renderer, image);
		SDL_FreeSurface(image);//frees up surface space	

	}

	RotateVal = _spriteNum * 45;//works out what degree the sprite should be rotated 
}

bool player::AaBbCollision(std::vector <Obstacle*> &_ObstacleVect)
{
	int playerLeft = position.x;
	int playerRight = position.x + position.w;
	int playerTop = position.y;
	int playerBottom = position.y + position.h;
	for (int i = 0; i < _ObstacleVect.size(); i++)//runs for every obstacle
	{
		int obstacleLeft = _ObstacleVect[i]->GetX()+20;
		int obstacleRight = _ObstacleVect[i]->GetX() + _ObstacleVect[i]->GetW()-45;// the +20 and -45 adjust for the sprite not entirely fitting inside the rect used for drawing it, this makes the collision more accurate
		int obstacleTop = _ObstacleVect[i]->GetY();
		int obstacleBottom = _ObstacleVect[i]->GetY() + _ObstacleVect[i]->GetH();

		//if the player is not touching the obstacle it returns false as there is no collision
		if (playerLeft >= obstacleRight)
		{
			return false;
		}
		if (playerRight <= obstacleLeft)
		{
			return false;

		}
		if (playerTop >= obstacleBottom)
		{
			return false;
		}
		if (playerBottom <= obstacleTop)
		{
			return false;
		}

		return true;//otherwise there is a colluision
	}
}
#pragma once
#ifndef _PLAYER_
#define _PLAYER_

#include "Game.h"
#include "GameObject.h"
#include <vector>

class GameObject;
class Obstacle;

class player : public GameObject
{

public:
	//constructors & Deconstructors
	player(bool _isDead, SDL_Renderer* _Renderer, const std::string _imgFile, int _x, int _y, int _w, int _h);
	~player();

	//getters
	bool getDead()
	{
		return isDead;
	}

	bool getIsJumping()
	{
		return isJumping;
	}

	//setters
	void setIsJumping(bool _isJumping)
	{
		isJumping = _isJumping;
	}


	void PlayerJump();

	void PlayerFall();

	void UpdateSprite(int _spriteNum);

	void SpriteDrawToScreen();

	bool AaBbCollision(std::vector <Obstacle*> &_ObstacleVect);

private:
	bool isDead;
	bool isJumping;
	int SpriteNum;
	int RotateVal;

};


#endif // !_PLAYER_

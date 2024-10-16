#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

//#include "Game.h"
#include <SDL.h>
#include <string>


class GameObject
{
public:
	//constructors & Deconstructors
	GameObject() = default;
	GameObject(SDL_Renderer* Renderer, const std::string _imgFile, int _x, int _y, int _w , int _h);
	~GameObject();

	//setters
	void SetX(int _x)
	{
		position.x = _x;
	}
	void SetY(int _y)
	{
		position.y = _y;
	}

	void setH(int _h)
	{
		position.h = _h;
	}

	void setW(int _w)
	{
		position.w = _w;
	}

	//getters
	int GetX()
	{
		return position.x;
	}
	int GetY()
	{
		return position.y;
	}
	int GetW()
	{
		return position.w;
	}
	int GetH()
	{
		return position.h;
	}

	SDL_Rect& GetRect() { return position; }
	
	virtual void SpriteDrawToScreen();

	void UpdateImage(std::string _imgFile);

protected://allows for inherted class to use these attributes
	 
	SDL_Rect position; // this defines where the gameobject is going to be and the width and hieght (the rectangle the gameobject will be)

	SDL_Renderer* Renderer;

	SDL_Texture* texImage;
};


#endif 

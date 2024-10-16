#include "Button.h"



Button::Button()
{
	isPressed = false;
	isHovering = false;
	mouseRect = { 0,0,1,1 };
}
//constuctor
Button::Button(bool _isPressed, bool _isHovering, SDL_Renderer* _Renderer, const std::string _imgFile, int _x, int _y, int _w, int _h):GameObject(_Renderer, _imgFile, _x,_y,_w,_h)
{
	isPressed = _isPressed;
	isHovering = _isHovering;
	mouseRect = { 0,0,1,1 };
}
//deconstructor
Button::~Button()
{

}

void Button::MouseHandling(SDL_Event* _MouseEvent,std::string _imgFile,std::string _imgFile2)
{

	if (_MouseEvent->type == SDL_MOUSEMOTION || _MouseEvent->type == SDL_MOUSEBUTTONDOWN || _MouseEvent->type == SDL_MOUSEBUTTONUP)//this runs if the mouse is either moving pressing a button or being released
	{
		
		SDL_GetMouseState(&mouseRect.x, &mouseRect.y);//stores the mouse x and y values 
		
		bool inButton = false;
		//checks to see if mouse is outside the button
		if (SDL_HasIntersection(&mouseRect, &position) && (_MouseEvent->type == SDL_MOUSEBUTTONDOWN || _MouseEvent->type == SDL_MOUSEBUTTONUP))
		{
			inButton = true;
			isHovering = false;
			isPressed = true;
		}
		if (SDL_HasIntersection(&mouseRect, &position))
		{
			isHovering = true;
		}
		else
		{
			isHovering = false;
		}

		if (isHovering)
		{
			if (isHoverImage == false)
			{
				isHoverImage = true;
				UpdateImage(_imgFile2.c_str());
			}
		}
		else
		{
			if (isHoverImage == true)
			{
				isHoverImage = false;
				UpdateImage(_imgFile.c_str());//change image to the normal version not the hovering version
			}
		}
		
	}
}
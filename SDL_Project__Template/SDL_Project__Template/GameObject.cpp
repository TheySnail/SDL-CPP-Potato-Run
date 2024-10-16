#include "GameObject.h"


GameObject::GameObject(SDL_Renderer* _Renderer, const std::string _imgFile, int _x, int _y, int _w, int _h)
{
	//sets the position of coordinates as well as the width of the image
	position.x = _x;
	position.y = _y;
	position.w = _w;
	position.h = _h;

	Renderer = _Renderer;
	SDL_Surface* image = SDL_LoadBMP(_imgFile.c_str());//creates surface from file specified

	//SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0, 0xFF, 0xFF));

	texImage = SDL_CreateTextureFromSurface(Renderer, image);

	SDL_FreeSurface(image);//frees up surface space

}

GameObject::~GameObject()
{
	delete Renderer;
	delete texImage;
	
}



void GameObject::SpriteDrawToScreen()
{
	/*SDL_Rect RepresentationHitBox = { position.x+20,position.y,position.w-45,position.h };*/
	/*SDL_RenderDrawRect(Renderer, &RepresentationHitBox);*/
	SDL_RenderCopy(Renderer, texImage,0, &position);//puts the gameobject to the renderer
}


void GameObject::UpdateImage(std::string _imgFile)
{
	SDL_Surface* image = SDL_LoadBMP(_imgFile.c_str());//creates surface from file specified

	//SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0, 0xFF, 0xFF));

	if (texImage != nullptr)
	{
		SDL_DestroyTexture(texImage);
	}

	texImage = SDL_CreateTextureFromSurface(Renderer, image);
	SDL_FreeSurface(image);//frees up surface space
}

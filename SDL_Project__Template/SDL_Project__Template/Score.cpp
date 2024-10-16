#include "Score.h"


void initScoreTxt(SDL_Renderer* _renderer, std::vector <SDL_Texture*>& _txtVect)
{
	TTF_Font* font{ nullptr };
	font = TTF_OpenFont("CuteDino.ttf", 128);//init font
	if (!font)
	{
		std::cout << "Failure opening font  : " << TTF_GetError() << std::endl;
	}


	SDL_Surface* text;

	SDL_Color colour = { 0,0,0 };//font colour

	//zero
	text = TTF_RenderText_Solid(font, "0", colour);//creates a surface with the font text

	SDL_Texture* text_texture;

	text_texture = SDL_CreateTextureFromSurface(_renderer, text);//creates a texture from that font

	_txtVect.push_back(text_texture);//pushes texture into vector

	SDL_FreeSurface(text);//frees the surface so it can be used again

	//one
	text = TTF_RenderText_Solid(font, "1", colour);

	text_texture = SDL_CreateTextureFromSurface(_renderer, text);

	_txtVect.push_back(text_texture);

	SDL_FreeSurface(text);

	//two
	text = TTF_RenderText_Solid(font, "2", colour);

	text_texture = SDL_CreateTextureFromSurface(_renderer, text);

	_txtVect.push_back(text_texture);

	SDL_FreeSurface(text);

	//three
	text = TTF_RenderText_Solid(font, "3", colour);

	text_texture = SDL_CreateTextureFromSurface(_renderer, text);

	_txtVect.push_back(text_texture);

	SDL_FreeSurface(text);
	
	//four
	text = TTF_RenderText_Solid(font, "4", colour);

	text_texture = SDL_CreateTextureFromSurface(_renderer, text);

	_txtVect.push_back(text_texture);

	SDL_FreeSurface(text);

	//five
	text = TTF_RenderText_Solid(font, "5", colour);

	text_texture = SDL_CreateTextureFromSurface(_renderer, text);

	_txtVect.push_back(text_texture);

	SDL_FreeSurface(text);

	//six
	text = TTF_RenderText_Solid(font, "6", colour);

	text_texture = SDL_CreateTextureFromSurface(_renderer, text);

	_txtVect.push_back(text_texture);

	SDL_FreeSurface(text);

	//seven
	text = TTF_RenderText_Solid(font, "7", colour);

	text_texture = SDL_CreateTextureFromSurface(_renderer, text);

	_txtVect.push_back(text_texture);

	SDL_FreeSurface(text);

	//eight
	text = TTF_RenderText_Solid(font, "8", colour);

	text_texture = SDL_CreateTextureFromSurface(_renderer, text);

	_txtVect.push_back(text_texture);

	SDL_FreeSurface(text);


	//nine
	text = TTF_RenderText_Solid(font, "9", colour);

	text_texture = SDL_CreateTextureFromSurface(_renderer, text);

	_txtVect.push_back(text_texture);

	SDL_FreeSurface(text);
}


void displayScore(SDL_Renderer* _renderer, std::vector <SDL_Texture*>& _txtVect, int _score)
{
	int units = 0;
	int ten = 0;
	int hundreds = 0;
	int thousand = 0;

	int fontWidth = 30;
	int fontHieght = 60;

	//breaks up the number into units , tens, hundreds, thousands
	units = _score % 10;
	ten = (_score / 10) % 10;
	hundreds = (_score / 100) % 10;
	thousand = (_score / 1000);

	/*std::cout << units << std::endl << ten << std::endl << hundreds << std::endl << thousand << std::endl;*/



	SDL_Rect thousandPlace = { 1100, 20, fontWidth,fontHieght };
	SDL_Rect hundredsPlace = { 1100+fontWidth, 20, fontWidth,fontHieght };
	SDL_Rect tensPlace = { 1100 + (fontWidth*2), 20, fontWidth,fontHieght };
	SDL_Rect unitPlace = { 1100 + (fontWidth * 3), 20, fontWidth,fontHieght };



	SDL_RenderCopy(_renderer, _txtVect[thousand],0, &thousandPlace);
	SDL_RenderCopy(_renderer, _txtVect[hundreds], 0, &hundredsPlace);
	SDL_RenderCopy(_renderer, _txtVect[ten], 0, &tensPlace);
	SDL_RenderCopy(_renderer, _txtVect[units], 0, &unitPlace);
}

void displayHighScore(SDL_Renderer* _renderer, std::vector <SDL_Texture*>& _txtVect, int _score,int _x, int _y)
{

	int x = _x;
	int y = _y;

	int units = 0;
	int ten = 0;
	int hundreds = 0;
	int thousand = 0;

	int fontWidth = 30;
	int fontHieght = 60;

	//breaks up the number into units , tens, hundreds, thousands
	units = _score % 10;
	ten = (_score / 10) % 10;
	hundreds = (_score / 100) % 10;
	thousand = (_score / 1000);

	/*std::cout << units << std::endl << ten << std::endl << hundreds << std::endl << thousand << std::endl;*/



	SDL_Rect thousandPlace = { x, y, fontWidth,fontHieght };
	SDL_Rect hundredsPlace = { x + fontWidth, y, fontWidth,fontHieght };
	SDL_Rect tensPlace = { x + (fontWidth * 2), y, fontWidth,fontHieght };
	SDL_Rect unitPlace = { x + (fontWidth * 3), y, fontWidth,fontHieght };



	SDL_RenderCopy(_renderer, _txtVect[thousand], 0, &thousandPlace);
	SDL_RenderCopy(_renderer, _txtVect[hundreds], 0, &hundredsPlace);
	SDL_RenderCopy(_renderer, _txtVect[ten], 0, &tensPlace);
	SDL_RenderCopy(_renderer, _txtVect[units], 0, &unitPlace);
}
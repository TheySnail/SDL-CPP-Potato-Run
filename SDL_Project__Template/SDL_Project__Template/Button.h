#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "GameObject.h"


class Button :
    public GameObject
{
public:
    //constructors & Deconstructors
    Button();
    Button(bool _isPressed,bool _isHovering,SDL_Renderer* _Renderer, const std::string _imgFile, int _x, int _y, int _w, int _h);
    ~Button();

    void MouseHandling(SDL_Event* _MouseEvent, std::string _imgFile, std::string _imgFile2);

    bool GetState()//getter
    {
        return isPressed;
    }

    void SetState(bool _ButtonPressedState)//setter
    {
        isPressed = _ButtonPressedState;
    }

private: 
    bool isHoverImage{ false };
    bool isPressed;
    bool isHovering;
    SDL_Rect mouseRect;

};

#endif
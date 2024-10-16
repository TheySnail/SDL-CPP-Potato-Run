#pragma once

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "GameObject.h"



class Obstacle :
    public GameObject
{
public:
    //constructors & Deconstructors
    Obstacle(bool _offScreen, bool _isFlying, SDL_Renderer* _Renderer, const std::string _imgFile, int _x, int _y, int _w, int _h, int _speed);
    ~Obstacle();

    void ObjectScrollLeft();
    void DrawObjectToScreen();

    void RepopulateObject(bool _offScreen, bool _isFlying, int _x, int _y, int _w, int _h, int _speed);

    void UpdateSprite();

    void increaseSpeed(int _speed);

    //getters
    bool getOffScreen()
    {
        return offScreen;
    }

    bool getIsFlying()
    {
        return isFlying;
    }
    //setters
    void setOffScreen(bool _off)
    {
        offScreen = _off;
    }
    

private:
    bool offScreen;
    bool isFlying;
    int MovementSpeed;
    int x, y;
};

#endif // !_OBJECT_H_
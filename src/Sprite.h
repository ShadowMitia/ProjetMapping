//
//  Sprite.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 06/02/2018.
//
//

#pragma once

#include "ofMain.h"
#include "Face.h"
#include "shift.h"
#include "Box2D.h"


class SpriteObj{
public:
    ofVec2f positionInit;
    ofImage spriteImage;
    Face* face;
    b2World* world;
    virtual void draw(){};
};

class Avatar;
class AvatarDef: public SpriteObj{
public:
    Shift* s;
    Avatar* a;
    void draw(){};
};

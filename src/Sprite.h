//
//  Sprite.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 06/02/2018.
//
//

#pragma once

#include "ofMain.h"
//#include "Face.h"
#include "shift.h"
#include "Box2D.h"

class Face;
class SpriteObj{
public:
    ofVec2f positionInit;
    Face* face;
    Face* faceIni;
    b2World* world;
    virtual void draw(){};
    virtual ofVec2f getPositionTranform(){};
};

class Avatar;
class AvatarDef: public SpriteObj{
public:
    ofImage spriteImage;
    Shift* s;
    Avatar* a;
    void draw();
    ofVec2f getPositionTranform();
};


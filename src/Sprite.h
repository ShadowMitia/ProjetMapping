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

    Face* face;

    virtual void draw(){};
    virtual ofVec2f getPositionTranform(){};
    virtual void reset(){};
    
    ofVec2f positionInit;
    Face* faceIni;
    b2World* world;
    
};

class Avatar;
class AvatarDef: public SpriteObj{
public:
    ofImage spriteImage;
    Shift* s;
    Avatar* a;
    void draw();
    ofVec2f getPositionTranform();
    void reset();
};


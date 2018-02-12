//
//  Sprite.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 06/02/2018.
//
//

#pragma once

#include "ofMain.h"
#include "shift.h"

class WorldsBox2d;
class Face;
class SpriteObj{
public:

    Face* face;
    virtual void draw(){};
    virtual ofVec2f getPositionTranform(){};
    virtual void create(){};
    virtual void reset(){};
    virtual bool isActif(){};

    
    ofVec2f positionInit;
    Face* faceIni;
    //b2World* world;
    WorldsBox2d* world;
    
};

class Avatar;
class AvatarDef: public SpriteObj{
public:
    ofImage spriteImage;
    Shift* s;
    Avatar* a;
    void draw()override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
};

class ObjBlock;
class ObjBlockDef: public SpriteObj{
public:
    ofImage spriteImage;
    ObjBlock * b;
    void draw() override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;

    
};

class ObjPickup;
class ObjPickupDef: public SpriteObj {
public:
    bool actif  = true;
    ofImage spriteImage;
    ObjPickup * pkup;
    void draw() override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;

};



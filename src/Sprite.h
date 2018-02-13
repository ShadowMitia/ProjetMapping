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
#include "b2Fixture.h"

/*
 Category bits:
 PLATFORM : 0x0001
 PORTAL   : 0x0002
 LADDER   : 0x0004
 CLONE    : 0x0008
 AVATAR   : 0x0010
 BLOCK    : 0x0020
 PICKUP   : 0x0040
 MUSHROOM : 0x0080
 */

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
    virtual void setFilter(){};

    int layer = 0;
    ofVec2f positionInit;
    Face* faceIni;
    //b2World* world;
    WorldsBox2d* world;
    
};

class Avatar;
class AvatarDef: public SpriteObj{
public:
    AvatarDef(){
        filterAvatar.categoryBits = 0x0010;
        filterAvatar.maskBits = 0x0001 | 0x0002 | 0x0004 | 0x0008 | 0x0010 | 0x0020 | 0x0040 | 0x0080;
    }
    b2Filter filterAvatar;
    ofImage spriteImage;
    Shift* s;
    Avatar* a;
    void draw()override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    void setFilter() override;
};

class ObjBlock;
class ObjBlockDef: public SpriteObj{
public:
    ObjBlockDef(){
        filterObjBlock.categoryBits = 0x0020;
        filterObjBlock.maskBits = 0x0001 | 0x0002 | 0x0008 | 0x0010 |0x0020 | 0x0040 | 0x0080;
    }
    b2Filter filterObjBlock;
    ofImage spriteImage;
    ObjBlock * b;
    void draw() override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    void setFilter() override;

    
};

class ObjPickup;
class ObjPickupDef: public SpriteObj {
public:
    
    ObjPickupDef(){
        filterObjPickup.categoryBits = 0x0040;
        filterObjPickup.maskBits = 0x0001 | 0x0002 | 0x0008 | 0x0010 | 0x0020 | 0x0080;
    }
    b2Filter filterObjPickup;
    bool actif  = true;
    ofImage spriteImage;
    ObjPickup * pkup;
    void draw() override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    void setFilter() override;

};

class ObjMushroom;
class ObjMushroomDef: public SpriteObj{
public:
    ObjMushroomDef(){
        filterObjMushroom.categoryBits = 0x0080;
        filterObjMushroom.maskBits =  0x0010 | 0x0008 ;
        layer = 1;
    }
    
    b2Filter filterObjMushroom;
    ofImage spriteImage;
    ObjMushroom * mroom;
    void draw() ;
    ofVec2f getPositionTranform() ;
    void create() ;
    void reset() ;
    bool isActif();
    
    
    
};



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
#include "Light.h"

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

/* Layer
 Layer 0 -> background
 Layer 1 -> Ombres platforms & objets
 Layer 2 -> Platforms & objets
 Layer 3 -> Avatar & Light
 Layer 4 -> Mushroom (top)
 Layer 5 -> Ombres on Mushroom
 Layer 6 -> Objets
 Layer 7 -> Avatar & Light
 Layer 8 -> Mask
 */

class WorldsBox2d;
class Face;
class SpriteObj{
public:

    Face* face;
    virtual void draw(){};
	virtual ofVec2f getPositionTranform() { return ofVec2f(0.0); };
    virtual void create(){};
    virtual void reset(){};
	virtual bool isActif() { return true; };
	virtual bool getViewPoint() { return true; };

    int layerId,layerIni;
    ofVec2f positionInit;
    Face* faceIni;
    //b2World* world;
    WorldsBox2d* world;
    uint16 categoryBits;
    uint16 maskBits;

    
};

class Avatar;
class AvatarDef: public SpriteObj, public Light{
public:
    AvatarDef(){
        categoryBits = 0x0010;
        maskBits  = 0x0001 | 0x0002 | 0x0004 | 0x0008 | 0x0010 | 0x0020 | 0x0040 | 0x0080;
        layerIni = layerId =  3;
        color.set(ofColor::orange);
    }
    ofImage spriteImage;
    Shift* s;
    Avatar* a;
    void draw()override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    bool getViewPoint() override;

    
};

class ObjBlock;
class ObjBlockDef: public SpriteObj{
public:
    ObjBlockDef(){
        categoryBits = 0x0020;
        maskBits = 0x0001 | 0x0002 | 0x0008 | 0x0010 |0x0020 | 0x0040 | 0x0080;
        layerIni = layerId =  2;
    }
    ofImage spriteImage;
    ObjBlock * b;
    void draw() override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    bool getViewPoint() override;

    
};

class ObjPickup;
class ObjPickupDef: public SpriteObj, public Light {
public:
    
    ObjPickupDef(){
        categoryBits = 0x0040;
        maskBits = 0x0001 | 0x0002 | 0x0008 | 0x0010 | 0x0020 | 0x0080;
        radius = 0.2;
        layerIni = layerId =  3;
        color.set(ofColor::yellow);
    }
    bool actif  = true;
    ofImage spriteImage;
    ObjPickup * pkup;
    void draw() override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    bool getViewPoint() override;

};

class ObjMushroom;
class ObjMushroomDef: public SpriteObj{
public:
    ObjMushroomDef(){
        categoryBits = 0x0080;
        maskBits =  0x0010 | 0x0008 ;
        layerIni = layerId =  4;
    }
    
    ofImage spriteImage;
    ObjMushroom * mroom;
    void draw() ;
    ofVec2f getPositionTranform() ;
    void create() ;
    void reset() ;
    bool isActif();
    bool getViewPoint(){return false;};
    
    
};



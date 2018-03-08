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


enum Category {
    
    PLATFORM       = 0x0001,
    PLATFORM_1     = 0x0002,
    PLATFORM_2     = 0x0004,
    PORTAL         = 0x0008,
    LADDER         = 0x0010,
    AVATAR         = 0x0020,
    CLONE           = 0x0040,
    OBJ            = 0x0080,
    OBJ_top        = 0x0100,
    MUSHROOM_top    = 0x0200,
       //= 0x0400,
    
    
};

/*
 Category bits:
 PLATFORM       : 0x0001
 PLATFORM-1     : 0x0002
 PLATFORM-2     : 0x0004
 PORTAL         : 0x0008
 LADDER         : 0x0010
 AVATAR         : 0x0020
 AVATAR-top     : 0x0040
 OBJ            : 0x0080
 OBJ-top        : 0x0100
 MUSHROOM-top   : 0x0200
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
    bool ViewPoint =  false;
    
};

class Avatar;
class AvatarDef: public SpriteObj, public Light{
public:
    AvatarDef(){
        categoryBits = Category::AVATAR;
        maskBits  =  Category::AVATAR  | Category::PORTAL | Category::LADDER |Category::OBJ;
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
        categoryBits = Category::OBJ;
        maskBits = Category::PORTAL | Category::AVATAR | Category::OBJ ;
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
        categoryBits = Category::OBJ;
        maskBits = Category::PORTAL | Category::AVATAR | Category::OBJ ;
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
        categoryBits = Category::OBJ;
        //maskBits =  Category::AVATAR | Category::OBJ | Category::CLONE ;
        maskBits = Category::CLONE ;
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

class ObjTrampoline;
class ObjTrampolineDef: public SpriteObj{
    ObjTrampolineDef(){
        categoryBits = Category::OBJ;
        maskBits = Category::PORTAL | Category::AVATAR | Category::OBJ ;
        layerIni = layerId =  2;
    }
    
    void draw() override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    bool getViewPoint() override;
    
    
};


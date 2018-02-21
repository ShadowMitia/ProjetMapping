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

/*  Layer
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
    virtual ofVec2f getPositionTranform(){};
    virtual void create(){};
    virtual void reset(){};
    virtual bool isActif(){};
    virtual void setFilter( b2Filter filter){};
    virtual b2Filter getFilter(){
        b2Filter temp;
        return temp;};
    virtual bool getViewPoint(){};

    int layer,layerIni;
    ofVec2f positionInit;
    Face* faceIni;
    //b2World* world;
    WorldsBox2d* world;
    
};

class Avatar;
class AvatarDef: public SpriteObj, public Light{
public:
    AvatarDef(){
        filterAvatar.categoryBits = 0x0010;
        filterAvatar.maskBits = 0x0001 | 0x0002 | 0x0004 | 0x0008 | 0x0010 | 0x0020 | 0x0040 | 0x0080;
        layerIni = layer =  3;
        color.set(ofColor::orange);
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
    void setFilter(b2Filter filter) override;
    b2Filter getFilter(){ return filterAvatar;} ;
    bool getViewPoint() override;

};

class ObjBlock;
class ObjBlockDef: public SpriteObj{
public:
    ObjBlockDef(){
        filterObjBlock.categoryBits = 0x0020;
        filterObjBlock.maskBits = 0x0001 | 0x0002 | 0x0008 | 0x0010 |0x0020 | 0x0040 | 0x0080;
        layerIni = layer =  2;
    }
    b2Filter filterObjBlock;
    ofImage spriteImage;
    ObjBlock * b;
    void draw() override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    void setFilter(b2Filter filter) override;
    b2Filter getFilter(){return filterObjBlock;};
    bool getViewPoint() override;

    
};

class ObjPickup;
class ObjPickupDef: public SpriteObj, public Light {
public:
    
    ObjPickupDef(){
        filterObjPickup.categoryBits = 0x0040;
        filterObjPickup.maskBits = 0x0001 | 0x0002 | 0x0008 | 0x0010 | 0x0020 | 0x0080;
        radius = 0.2;
        layerIni = layer =  3;
        color.set(ofColor::yellow);
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
    void setFilter(b2Filter filter) override;
    b2Filter getFilter(){return filterObjPickup;};
    bool getViewPoint() override;

};

class ObjMushroom;
class ObjMushroomDef: public SpriteObj{
public:
    ObjMushroomDef(){
        filterObjMushroom.categoryBits = 0x0080;
        filterObjMushroom.maskBits =  0x0010 | 0x0008 ;
        layerIni = layer =  4;
    }
    
    b2Filter filterObjMushroom;
    ofImage spriteImage;
    ObjMushroom * mroom;
    void draw() ;
    ofVec2f getPositionTranform() ;
    void create() ;
    void reset() ;
    bool isActif();
    bool getViewPoint(){return false;};
    
    
};



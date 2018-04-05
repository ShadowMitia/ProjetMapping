#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
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

std::vector<ofPoint> loadPoints(const std::string& file);


enum class Sprite {UNKNOWN, AVATAR, CLONE, PLATFORM, BLOCK, PICKUP, PORTAL ,LADDER, MUSHROOM, sensorAVATAR, SignageSign};
class PhysicalizedElement;

struct dataSprite {
    PhysicalizedElement* physicalizedElement;
    Sprite sprite = Sprite::UNKNOWN;
};
class PhysicalizedElement {

public:
    
	virtual void contactStart(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite);
	virtual void contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite);
	virtual void PostSolve(b2Fixture* _fixture,dataSprite* OtherSprite, const b2ContactImpulse* impulse) {}
    virtual void PreSolve(b2Fixture* _fixture,dataSprite* OtherSprite,ofxBox2dPreContactArgs e){};
};
class ObjectGame: public ofxBox2dPolygon{
public:
    void    createObjMushroom(b2World * b2dworld, bool _detectSide);
    void    create(b2World * b2dworld, bool _detectSide);
    void    setFilterDataObjet(b2Filter _filter);
    void    setFilterDataSide(b2Filter _filter);
    //b2Filter FilterDataObjet,FilterDataSide;
    int tabCollision[5] = {0}; //faire un pt tab ou new tab[1] ou new tab[5];
};
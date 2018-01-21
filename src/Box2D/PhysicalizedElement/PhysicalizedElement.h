#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

/*
 Category bits:
 AVATAR : 0x0001
 SIDE : 0x0002
 PICKUP : 0x0004
 BLOCK : 0x0008
 PLATFORM : 0x0016
 PORTAL : 0x0032
 CLONE : 0x0064
 LADDER : 0x0128
 */

enum class Sprite {UNKNOWN, AVATAR, CLONE, FOOT, WATER, PLATFORM, BLOCK, PICKUP, PORTAL, SIDE,LADDER};
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
    void    create(b2World * b2dworld, bool _detectSide);
    void    setFilterDataObjet(b2Filter _filter);
    void    setFilterDataSide(b2Filter _filter);
    b2Filter FilterDataObjet,FilterDataSide;
    bool tabCollision[5]; //faire un pt tab ou new tab[1] ou new tab[5];
};
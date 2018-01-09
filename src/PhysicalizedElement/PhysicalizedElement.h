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
 */

enum class Sprite {UNKNOWN, AVATAR, CLONE, FOOT, WATER, PLATFORM, BLOCK, PICKUP, PORTAL, SIDE};
enum class Side{ UP, DOWN, LEFT, RIGHT};
class PhysicalizedElement;

struct dataSprite {
    PhysicalizedElement* physicalizedElement;
    Sprite sprite = Sprite::UNKNOWN;
};
struct dataSpriteSide: dataSprite{
    Side side = Side::DOWN;
};
class PhysicalizedElement {

public:
    
	virtual void contactStart(b2Fixture* _fixture, dataSprite* OtherSprite);
	virtual void contactEnd(b2Fixture* _fixture, dataSprite* OtherSprite);
	virtual void PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse) {}
};
class ObjectGame: public ofxBox2dPolygon{
public:
    void    create(b2World * b2dworld, bool _detectSide);
    void    setFilterDataObjet(b2Filter _filter);
    void    setFilterDataSide(b2Filter _filter);
    b2Filter FilterDataObjet,FilterDataSide;
    
};
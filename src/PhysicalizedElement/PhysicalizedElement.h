#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"


/*
 Category bits:
 AVATAR : 0x0001
 AVATAR_FOOT : 0x0002
 PICKUP : 0x0004
 BLOCK : 0x0008
 PLATFORM : 0x0016
 PORTAL : 0x0032
 CLONE : 0x0064
 */

enum class Sprite {UNKNOWN, AVATAR, CLONE, FOOT, WATER, PLATFORM, BLOCK, PICKUP, PORTAL};

class PhysicalizedElement;
struct dataSprite {
    PhysicalizedElement* physicalizedElement;
    Sprite sprite = Sprite::UNKNOWN;
};

class PhysicalizedElement {

public:
    
	virtual void contactStart(dataSprite* OtherSprite);
	virtual void contactEnd(dataSprite* OtherSprite);
	virtual void PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse) {}
};

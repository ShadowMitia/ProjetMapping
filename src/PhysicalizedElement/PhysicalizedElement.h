#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"

class dataSprite;

class PhysicalizedElement {

public:
	virtual void contactStart(dataSprite* OtherSprite);
	virtual void contactEnd(dataSprite* OtherSprite);

};
#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "FboSource.h"

class Scene1 : public ofx::piMapper::FboSource
{
public:
	Scene1()
	{
		name = "Scene One FBO Source";
		allocate(500, 500);

		font.load("arial.ttf", 64);
	}

	void draw()
	{
		ofClear(0);
		ofBackground(255, 0, 0, 255);

		ofSetColor(255);
		ofScale(100, 100, 100);
		font.drawString("1", 250, 250);
	}

	ofTrueTypeFont font;
};
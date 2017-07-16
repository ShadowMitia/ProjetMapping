#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "FboSource.h"

class Scene2 : public ofx::piMapper::FboSource
{
public:
	Scene2()
	{
		name = "Scene Two FBO Source";
		allocate(100, 100);
	}

	void draw()
	{
		ofClear(0);
		ofBackground(0, 255, 0, 255);

		ofSetColor(255);
		ofDrawBitmapString("2", 50, 50);
	}
};
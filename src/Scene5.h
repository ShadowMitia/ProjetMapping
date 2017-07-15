#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "FboSource.h"

class Scene5 : public ofx::piMapper::FboSource
{
public:
	Scene5()
	{
		name = "Scene Five FBO Source";
		allocate(500, 500);
	}

	void draw()
	{
		ofClear(0);
		ofBackground(255, 255, 0, 255);

		ofSetColor(255);
		ofDrawBitmapString("5", 250, 250);
	}
};
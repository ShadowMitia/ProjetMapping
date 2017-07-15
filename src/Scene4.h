#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "FboSource.h"

class Scene4 : public ofx::piMapper::FboSource
{
public:
	Scene4()
	{
		name = "Scene Four FBO Source";
		allocate(500, 500);
	}

	void draw()
	{
		ofClear(0);
		ofBackground(255, 0, 255, 255);

		ofSetColor(255);
		ofDrawBitmapString("4", 250, 250);
	}
};
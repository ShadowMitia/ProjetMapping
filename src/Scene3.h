#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "FboSource.h"

class Scene3 : public ofx::piMapper::FboSource
{
public:
	Scene3()
	{
		name = "Scene Three FBO Source";
		allocate(100, 100);
	}

	void draw()
	{
		ofClear(0);
		ofBackground(0, 0, 255, 255);

		ofSetColor(255);
		ofDrawBitmapString("3", 50, 50);
	}
};
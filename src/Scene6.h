#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "FboSource.h"

class Scene6 : public ofx::piMapper::FboSource
{
public:
	Scene6()
	{
		name = "Scene Six FBO Source";
		allocate(100, 100);
	}

	void draw()
	{
		ofClear(0);
		ofBackground(200, 200, 200, 255);

		ofSetColor(255);
		ofDrawBitmapString("6", 50, 50);
	}
};
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
		allocate(600, 300);

	}

	void draw()
	{
		ofClear(0);
		ofBackground(200, 0, 0, 255);
        //ofDrawBitmapString("1", 50, 50);
        ofSetColor(ofColor::white);
        ofSetLineWidth(1);
        for (int i=0; i<=600; i+=50) {
            ofDrawLine(i, 0, i, 300);
        }
        for (int i=0; i<=300; i+=50) {
            ofDrawLine(0, i, 1200, i);
        }
	}
};
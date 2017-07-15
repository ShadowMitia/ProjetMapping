#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPiMapper.h"
#include "FboSource.h"

class Scene : public ofx::piMapper::FboSource
{
public:
	Scene()
	{
		name = "Scene FBO Source";
		allocate(500, 500);
	}

	void draw()
	{
		ofClear(0);
		ofSetColor(255, 255, 0, 255);

		ofDrawRectangle(0, 0, getWidth(), getHeight());

		ofSetColor(0, 0, 0, 255);
		ofSetLineWidth(5);

		float y = sin(float(ofGetFrameNum()) / 10.0f) * 100.0f;

		ofPoint startPoint = ofPoint(10, y);
		ofPoint endPoint = ofPoint(getWidth() - 10, getHeight() - y);

		ofDrawLine(startPoint, endPoint);

		float tempY = startPoint.y;
		startPoint.y = endPoint.y;
		endPoint.y = tempY;

		ofDrawLine(startPoint, endPoint);
	}
};

class SceneAlex : public ofx::piMapper::FboSource
{
public:
	SceneAlex()
	{
		name = "Scene Alex FBO Source";
		allocate(500, 500);

		img.load("tigrou.jpg");
	}

	void draw()
	{
		img.draw(0, 0, 300, 300);
	}

	ofImage img;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxPiMapper mapping;

		Scene* scene;
		SceneAlex* sceneAlex;
		
};

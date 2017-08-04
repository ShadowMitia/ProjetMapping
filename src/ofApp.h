#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPiMapper.h"
#include "ofxBox2d.h"
#include "EditorPlatform.h"

#include "ScenesMapping.h"
#include "Avatar.h"


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
        WorldsBox2d* worlds; // les mondes Box2d
    

		Scene1* scene1;
		Scene2* scene2;
		Scene3* scene3;
		Scene4* scene4;
		Scene5* scene5;
		Scene6* scene6;
    
        EditorPlatform editorPlatform;
		
};

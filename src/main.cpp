#include "ofMain.h"
#include "ofApp.h"

#define Debug_scene 1



//========================================================================
int main( ){
	ofSetupOpenGL(2000,600,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}

#include "ofMain.h"
#include "ofApp.h"
#include "Constant.h"

#define DEBUGTOTAL
#define Debug_World


//========================================================================
int main( ){
	ofSetupOpenGL(1296/2, 624/2, OF_WINDOW);			// <-------- setup the GL context

    // this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}

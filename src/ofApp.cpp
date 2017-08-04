#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
    
    worlds =new WorldsBox2d;
    worlds->setup();
    
	scene1 = new Scene1(worlds);
	scene2 = new Scene2();
	scene3 = new Scene3();
	scene4 = new Scene4();
	scene5 = new Scene5();
	scene6 = new Scene6();

	mapping.registerFboSource(scene1);
	mapping.registerFboSource(scene2);
	mapping.registerFboSource(scene3);
	mapping.registerFboSource(scene4);
	mapping.registerFboSource(scene5);
	mapping.registerFboSource(scene6);

	mapping.setup();
    
    worlds->createAvatar();

}

//--------------------------------------------------------------
void ofApp::update(){
    

    editorPlatform.update();
    worlds->update();
    //mapping.update();


}

//--------------------------------------------------------------
void ofApp::draw(){

    scene1->draw();
    ofSetColor(ofColor::aqua);
    editorPlatform.polylineFinal.draw();


    //mapping.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
#ifdef DEBUGTOTAL
    #ifdef Debug_World
        for (auto &avatar : worlds->avatars) {
        avatar.handleInputs(key);
    }
    #else
        mapping.keyPressed(key);
    #endif
    #else
        for (auto &avatar : worlds->avatars) {
        avatar.handleInputs(key);
    }
#endif
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if (key == 'C') {
        worlds->createPlatform(editorPlatform.getPoly());
    }
    if (key == 'E') {
        editorPlatform.platformWordExport(worlds->platforms);
    }
    if (key == 'I') {
        worlds->platforms.clear();
        vector<ofPolyline>  platforms = editorPlatform.platformWordImport();
        for (int i =0; i < platforms.size(); i++) {
            worlds->createPlatform(platforms[i]);
        }
    }
    
    editorPlatform.keyPressed(key);

    //mapping.keyReleased(key);


}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    editorPlatform.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

    //mapping.mouseDragged(x, y, button);

	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    //mapping.mousePressed(x, y, button);

	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    //mapping.mouseReleased(x, y, button);


}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

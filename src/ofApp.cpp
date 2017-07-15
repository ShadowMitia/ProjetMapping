#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);

	scene = new Scene();
	sceneAlex = new SceneAlex();
	mapping.registerFboSource(scene);
	mapping.registerFboSource(sceneAlex);

	mapping.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	mapping.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	mapping.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	mapping.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	mapping.keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	mapping.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mapping.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	mapping.mouseReleased(x, y, button);
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

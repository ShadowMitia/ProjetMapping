#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0);
    
    worlds =new WorldsBox2d;
    worlds->initWordldsBox2d();
    
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
    

}

//--------------------------------------------------------------
void ofApp::update(){
    worlds->updateWorldsBox2d();
	mapping.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	mapping.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	mapping.keyPressed(key);
    if (key=='c') {
        worlds->creatCircle(mouseX, mouseY);
    }
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

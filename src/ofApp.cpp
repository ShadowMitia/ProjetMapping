#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);

    worlds =new WorldsBox2d;
    lightSystem = new ofx::LightSystem2D;
    lightSystem->setup();
    worlds->setup(lightSystem);
    
	scene1 = new Scene1(worlds, lightSystem);
	scene2 = new Scene2(worlds, lightSystem);

	mapping.registerFboSource(scene1);
	mapping.registerFboSource(scene2);


	mapping.setup();

    //importPortial();


}

//--------------------------------------------------------------
void ofApp::update(){
    editorPlatform.update();
    worlds->update();
    lightSystem->update();
    //mapping.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    scene2->draw();
    ofSetColor(ofColor::aqua);
    editorPlatform.polylineFinal.draw();


    //mapping.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

  for (auto &avatar : worlds->avatars) {
    if (key == OF_KEY_LEFT || key == 'q')
      {
	avatar.goingLeft(true);
      }

    if (key == OF_KEY_RIGHT || key == 'd')
      {

	avatar.goingRight(true);
      }

    if (key == ' ')
      {
	avatar.jump();
      }
  }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){


  for (auto &avatar : worlds->avatars) {
    if (key == OF_KEY_LEFT || key == 'q')
      {
	avatar.goingLeft(false);
      }

      if (key == OF_KEY_RIGHT || key == 'd')
      {
	avatar.goingRight(false);
      }
  }

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

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);

    worlds =new WorldsBox2d;
    lightSystem = new ofx::LightSystem2D;
    lightSystem->setup();
    worlds->setup(lightSystem);
    
	scene1 = new Scene1(worlds, lightSystem);
	scene2 = new Scene2();

	mapping.registerFboSource(scene1);
	mapping.registerFboSource(scene2);


	mapping.setup();
    
	worlds->createAvatar(100, 100);
    //importPortial();
    worlds->world.enableEvents();    

    ofAddListener(worlds->world.contactStartEvents, this, &ofApp::contactStart);
    ofAddListener(worlds->world.contactEndEvents, this, &ofApp::contactEnd);

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

    scene1->draw();
    ofSetColor(ofColor::aqua);
    editorPlatform.polylineFinal.draw();


    //mapping.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

    for (auto &avatar : worlds->avatars) {
        if (key == OF_KEY_LEFT || key == 'q')
        {
            avatar.move(Direction::LEFT);
        }
        
        if (key == OF_KEY_RIGHT || key == 'd')
        {
            avatar.move(Direction::RIGHT);
        }
  }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
  for (auto &avatar : worlds->avatars) {
      dataAvatar * data = (dataAvatar*) avatar.polygon.getData();
      cout << data->jumping << endl;
      if (key == ' ' && data->jumping == false){
          avatar.move(Direction::JUMP);
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


//template<class Temp>
void ofApp::contactStart(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {}
    
    dataSprite* aSprite = (dataSprite*)e.a->GetBody()->GetUserData();
    dataSprite* bSprite = (dataSprite*)e.b->GetBody()->GetUserData();
    
    
    if (aSprite->getSprite() == Sprite::AVATRA && bSprite->getSprite() == Sprite::PLATFORM) {
        dataAvatar* aData = (dataAvatar*)e.a->GetBody()->GetUserData();
        aData->jumping=false;
    }
    if (bSprite->getSprite() == Sprite::AVATRA && aSprite->getSprite() == Sprite::PLATFORM) {
        dataAvatar* bData = (dataAvatar*)e.b->GetBody()->GetUserData();
        bData->jumping=false;
    }
    
}
void ofApp::contactEnd(ofxBox2dContactArgs &e){
    if(e.a != NULL && e.b != NULL) {}

    dataSprite* aSprite = (dataSprite*)e.a->GetBody()->GetUserData();
    dataSprite* bSprite = (dataSprite*)e.b->GetBody()->GetUserData();
    
    
    if (aSprite->getSprite() == Sprite::AVATRA && bSprite->getSprite() == Sprite::PLATFORM) {
        dataAvatar* aData = (dataAvatar*)e.a->GetBody()->GetUserData();
        aData->jumping=true;
    }
    if (bSprite->getSprite() == Sprite::AVATRA && aSprite->getSprite() == Sprite::PLATFORM) {
        dataAvatar* bData = (dataAvatar*)e.b->GetBody()->GetUserData();
        bData->jumping=true;
    }
}


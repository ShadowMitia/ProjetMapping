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

    /*
    for (auto &avatar : worlds->avatars) {
    cout << avatar.jumping << endl;
    
    }*/

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
            if (avatar.jumping) avatar.airControl(Direction::LEFT);
            else avatar.move(Direction::LEFT);
        }
        
        if (key == OF_KEY_RIGHT || key == 'd')
        {
            if (avatar.jumping) avatar.airControl(Direction::RIGHT);
            else avatar.move(Direction::RIGHT);
        }

  }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    
    for (auto &avatar : worlds->avatars) {
        
        if (key == ' ' && avatar.jumping == false){
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
    if(e.a != nullptr && e.b != nullptr) {}
    
    dataSprite* aSprite = (dataSprite*)e.a->GetBody()->GetUserData();
    dataSprite* bSprite = (dataSprite*)e.b->GetBody()->GetUserData();

    if (aSprite == nullptr || bSprite == nullptr) {
      return;
    }

    if (aSprite->getSprite() == Sprite::FOOT && bSprite->getSprite() == Sprite::PLATFORM) {
        dataFoot* aData = (dataFoot*)e.a->GetBody()->GetUserData();
        aData->avatarPtr->jumping = false;
        cout << "false a " << endl;
    }
    if (bSprite->getSprite() == Sprite::FOOT && aSprite->getSprite() == Sprite::PLATFORM) {
        dataFoot* bData = (dataFoot*)e.b->GetBody()->GetUserData();
        bData->avatarPtr->jumping = false;
        cout << "false b " << endl;
    }
    
}

void ofApp::contactEnd(ofxBox2dContactArgs &e){
    if(e.a != nullptr && e.b != nullptr) {}

    dataSprite* aSprite = (dataSprite*)e.a->GetBody()->GetUserData();
    dataSprite* bSprite = (dataSprite*)e.b->GetBody()->GetUserData();

    if (aSprite == nullptr || bSprite == nullptr) {
      return;
    }


    if (aSprite->getSprite() == Sprite::FOOT && bSprite->getSprite() == Sprite::PLATFORM) {
        dataFoot* aData = (dataFoot*)e.a->GetBody()->GetUserData();
        aData->avatarPtr->jumping = true;
    }

    if (bSprite->getSprite() == Sprite::FOOT && aSprite->getSprite() == Sprite::PLATFORM) {
        dataFoot* bData = (dataFoot*)e.b->GetBody()->GetUserData();
        bData->avatarPtr->jumping = true;
    }

    
}


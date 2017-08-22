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
#ifdef CUSTOM_BOX2D_TIM
	ofAddListener(worlds->world.PostSolveEvents, this, &ofApp::PostSolve);
	ofAddListener(worlds->world.PreSolveEvents,  this, &ofApp::PreSolve);
#endif // CUSTOM_BOX2D_TIM
    
    ////   Import Platform   /////
    worlds->platforms.clear();
    vector<ofPolyline>  platforms = editorPlatform.importImage();
    for (int i =0; i < platforms.size(); i++) {
        worlds->createPlatform(platforms[i]);
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    editorPlatform.update();
    worlds->update();
    //lightSystem->update();
    mapping.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    //scene1->draw();
    mapping.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) 
{
	for (auto &avatar : worlds->avatars) 
	{
		avatar.keyPressed(key);
	}
    mapping.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	for (auto &avatar : worlds->avatars)
	{
		avatar.keyReleased(key);
	}
    
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


void ofApp::contactStart(ofxBox2dContactArgs &e) 
{
	if (e.a != nullptr && e.b != nullptr)
	{
		dataSprite* aSprite = (dataSprite*)e.a->GetBody()->GetUserData();
		dataSprite* bSprite = (dataSprite*)e.b->GetBody()->GetUserData();

		if (aSprite == nullptr || bSprite == nullptr) 
		{
			return;
		}

		PhysicalizedElement* aPhysicalizedElement = aSprite->Element;
		PhysicalizedElement* bPhysicalizedElement = bSprite->Element;

		if (aPhysicalizedElement)
		{
			//aPhysicalizedElement->contactStart(bSprite);
		}
		if (bPhysicalizedElement)
		{
			//bPhysicalizedElement->contactStart(aSprite);
		}
	}
}

void ofApp::contactEnd(ofxBox2dContactArgs &e)
{
	if (e.a != nullptr && e.b != nullptr)
	{
		dataSprite* aSprite = (dataSprite*)e.a->GetBody()->GetUserData();
		dataSprite* bSprite = (dataSprite*)e.b->GetBody()->GetUserData();

		if (aSprite == nullptr || bSprite == nullptr)
		{
			return;
		}

		PhysicalizedElement* aPhysicalizedElement = aSprite->Element;
		PhysicalizedElement* bPhysicalizedElement = bSprite->Element;

		if (aPhysicalizedElement)
		{
			aPhysicalizedElement->contactEnd(bSprite);
		}
		if (bPhysicalizedElement)
		{
			bPhysicalizedElement->contactEnd(aSprite);
		}
	}
}

#ifdef CUSTOM_BOX2D_TIM
void ofApp::PreSolve(ofxBox2dPreContactArgs &e)
{

}

void ofApp::PostSolve(ofxBox2dPostContactArgs &e)
{
	if (e.a != nullptr && e.b != nullptr && e.impulse != nullptr)
	{
		dataSprite* aSprite = (dataSprite*)e.a->GetBody()->GetUserData();
		dataSprite* bSprite = (dataSprite*)e.b->GetBody()->GetUserData();

		if (aSprite == nullptr || bSprite == nullptr)
		{
			return;
		}

		PhysicalizedElement* aPhysicalizedElement = aSprite->Element;
		PhysicalizedElement* bPhysicalizedElement = bSprite->Element;

		if (aPhysicalizedElement)
		{
			aPhysicalizedElement->PostSolve(bSprite, e.impulse);
		}
		if (bPhysicalizedElement)
		{
			bPhysicalizedElement->PostSolve(aSprite, e.impulse);
		}
	}
}


#endif //CUSTOM_BOX2D_TIM


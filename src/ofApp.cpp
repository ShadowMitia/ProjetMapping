#include "ofApp.h"



vector<ofPolyline> importImage(const string& path){    
    ofImage image;
    vector<ofPolyline> poly;
    if (!image.load(path))
      {
		throw std::invalid_argument(path);
      }
    ofxCv::ContourFinder contourFinder;
    contourFinder.setMinAreaRadius(0);
    contourFinder.setMaxAreaRadius(1000); //1000 max
    contourFinder.setThreshold(100);
    contourFinder.setFindHoles(true);
    contourFinder.findContours(image);
    
    for (int i =0 ; i<contourFinder.getPolylines().size(); i++){
        ofPolyline tempPoly;
        tempPoly = contourFinder.getPolyline(i);
        tempPoly.addVertex(tempPoly.getVertices().at(0));
        poly.push_back(tempPoly);
    }
    return poly;
}


//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);

	worlds = new WorldsBox2d;
	worlds->setup();


	scene1 = new Scene1(worlds, "Map_prog_Plateformes_Test.png");
	scene2 = new Scene2(worlds);

	mapping.registerFboSource(scene1);
	mapping.registerFboSource(scene2);


	mapping.setup();

	//importPortial();
	worlds->world.enableEvents();

	ofAddListener(worlds->world.contactStartEvents, this, &ofApp::contactStart);
	ofAddListener(worlds->world.contactEndEvents, this, &ofApp::contactEnd);
#ifdef CUSTOM_BOX2D_TIM
	ofAddListener(worlds->world.PostSolveEvents, this, &ofApp::PostSolve);
	ofAddListener(worlds->world.PreSolveEvents, this, &ofApp::PreSolve);
#endif // CUSTOM_BOX2D_TIM

	////   Import Platform   /////
	worlds->platforms.clear();

	vector<ofPolyline>  platforms = importImage("Map_prog_Plateformes_Test.png");
	for (int i = 0; i < platforms.size() - 1; i++) {
		worlds->createPlatform(platforms[i]);
	}
	////   Import Ladder   /////
	/*
	vector<ofPolyline>  ladders = importImage("Map_prog_Echelles.png");
	for (int i =0; i<ladders.size()-1; i++) {
		worlds->createLadder(ladders[i]);
	}
	

	ofPolyline ladders;
	ladders.addVertex(0, 0);
	ladders.addVertex(0, 3520);
	ladders.addVertex(0, 800);
	ladders.addVertex(3520, 800);

	worlds->createLadder(ladders);
     */

    /*
    vector<ofPolyline> boxes = importImage("Test_Boite.png");
    for (int i = 0; i < boxes.size() - 1; i++)
      {
	worlds->createBox(boxes[i]);
      }
    */

#ifdef USE_WIIMOTE
	wiiuse.addListener(this);
#endif

}

//--------------------------------------------------------------
void ofApp::update(){
#ifdef USE_WIIMOTE
	wiiuse.update();
#endif
    input();
    worlds->update();
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
    for (int i = 0; i<worlds->avatars.size(); i++) {
        worlds->avatars[i]->keyPressed(key);
    }
    mapping.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    for (int i = 0; i<worlds->avatars.size(); i++) {
        worlds->avatars[i]->keyReleased(key);
    }
    
    mapping.keyReleased(key);

	if (key == 'f')
	{
		fullscreen = !fullscreen;
		ofSetFullscreen(fullscreen);
	}
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
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}

void ofApp::exit() {
#ifdef USE_WIIMOTE
	wiiuse.removeListener(this);
#endif
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
		dataSprite* aSprite = reinterpret_cast<dataSprite*>(e.a->GetBody()->GetUserData());
		dataSprite* bSprite = reinterpret_cast<dataSprite*>(e.b->GetBody()->GetUserData());

		if (aSprite == nullptr || bSprite == nullptr)
		{
			return;
		}

		PhysicalizedElement* aPhysicalizedElement = dynamic_cast<PhysicalizedElement*>(aSprite->Element);
		PhysicalizedElement* bPhysicalizedElement = dynamic_cast<PhysicalizedElement*>(bSprite->Element);

		if (aPhysicalizedElement != nullptr)
		{
		  aPhysicalizedElement->PostSolve(bSprite, e.impulse);
		}

		if (bPhysicalizedElement != nullptr)
		{
		  bPhysicalizedElement->PostSolve(aSprite, e.impulse);
		}
	}
}
#endif //CUSTOM_BOX2D_TIM

void ofApp::input() {

	bool temp[4];
	if (ofxGLFWJoystick::one().getAxisValue(0, 0) > 0.5 || ofxGLFWJoystick::one().getAxisValue(0, 0) < -0.5) {
		if (ofxGLFWJoystick::one().getAxisValue(0, 0)>0) {
			temp[1] = true;
			temp[0] = false;
		}
		else {
			temp[0] = true;
			temp[1] = false;
		}
	}
	else {
		temp[1] = false;
		temp[0] = false;
	}


	ofxGLFWJoystick::one().update();
	for (int joystickID = 0; joystickID < 1; joystickID++) {

		if (inputButton[joystickID][2] != ofxGLFWJoystick::one().getButtonValue(13, joystickID)) {
			if (!inputButton[joystickID][3])inputButton[joystickID][2] = ofxGLFWJoystick::one().getButtonValue(13, joystickID);
			if (!inputButton[joystickID][3] && !inputButton[joystickID][2])worlds->avatars[joystickID]->keyReleased(OF_KEY_LEFT);
			else worlds->avatars[joystickID]->keyPressed(OF_KEY_LEFT);
		}
		if (inputButton[joystickID][3] != ofxGLFWJoystick::one().getButtonValue(11, joystickID)) {
			if (!inputButton[joystickID][2])inputButton[joystickID][3] = ofxGLFWJoystick::one().getButtonValue(11, joystickID);

			if (!inputButton[joystickID][3])worlds->avatars[joystickID]->keyReleased(OF_KEY_RIGHT);
			else worlds->avatars[joystickID]->keyPressed(OF_KEY_RIGHT);
		}
		if (inputButton[joystickID][4] != ofxGLFWJoystick::one().getButtonValue(1, joystickID)) {
			inputButton[joystickID][4] = ofxGLFWJoystick::one().getButtonValue(1, joystickID);
			if (inputButton[joystickID][4]) worlds->avatars[joystickID]->keyPressed(' ');
			else worlds->avatars[joystickID]->keyReleased(' ');
		}
		if (inputButton[joystickID][5] != ofxGLFWJoystick::one().getButtonValue(2, joystickID)) {
			inputButton[joystickID][5] = ofxGLFWJoystick::one().getButtonValue(2, joystickID);

			if (inputButton[joystickID][5])worlds->avatars[joystickID]->keyPressed(OF_KEY_LEFT_CONTROL);
			else worlds->avatars[joystickID]->keyReleased(OF_KEY_LEFT_CONTROL);
		}
	}

}

#ifdef USE_WIIMOTE

void ofApp::onWiiuseControlEvent(ofxWiiuseControlEventArgs& args)
{

}

void ofApp::onWiiuseButtonEvent(ofxWiiuseButtonEventArgs& args)
{

	switch (args.second)
	{
	case OFXWIIUSE_BUTTON_UP_PRESSED:
	{
		worlds->avatars[args.first - 1]->keyPressed(OF_KEY_LEFT);
		break;
	}
	case OFXWIIUSE_BUTTON_DOWN_PRESSED:
	{
		worlds->avatars[args.first - 1]->keyPressed(OF_KEY_RIGHT);
		break;
	}
	case OFXWIIUSE_BUTTON_UP_RELEASED:
	{
		worlds->avatars[args.first - 1]->keyReleased(OF_KEY_LEFT);
		break;
	}
	case OFXWIIUSE_BUTTON_DOWN_RELEASED:
	{
		worlds->avatars[args.first - 1]->keyReleased(OF_KEY_RIGHT);
		break;
	}
	case OFXWIIUSE_BUTTON_LEFT_PRESSED:
	{
		worlds->avatars[args.first - 1]->keyPressed(OF_KEY_DOWN);
		break;
	}
	case OFXWIIUSE_BUTTON_LEFT_RELEASED:
	{
		worlds->avatars[args.first - 1]->keyReleased(OF_KEY_DOWN);
		break;
	}
	case OFXWIIUSE_BUTTON_RIGHT_PRESSED:
	{
		worlds->avatars[args.first - 1]->keyPressed(OF_KEY_UP);
		break;
	}
	case OFXWIIUSE_BUTTON_RIGHT_RELEASED:
	{
		worlds->avatars[args.first - 1]->keyReleased(OF_KEY_UP);
		break;
	}
	case OFXWIIUSE_BUTTON_ONE_PRESSED:
	{
		worlds->avatars[args.first - 1]->keyPressed(' ');
		break;
	}
	case OFXWIIUSE_BUTTON_ONE_RELEASED:
	{
		worlds->avatars[args.first - 1]->keyReleased(' ');
		break;
	}
	case OFXWIIUSE_BUTTON_TWO_PRESSED:
	{
		worlds->avatars[args.first - 1]->keyPressed(OF_KEY_LEFT_CONTROL);
		break;
	}
	case OFXWIIUSE_BUTTON_TWO_RELEASED:
	{
		worlds->avatars[args.first - 1]->keyReleased(OF_KEY_LEFT_CONTROL);
		break;
	}

	}
}

void ofApp::onWiiuseMotionEvent(ofxWiiuseMotionEventArgs& args)
{

}

void ofApp::onWiiuseIRTrackingEvent(ofxWiiuseIRTrackingEventArgs& args)
{
}

#endif

#include "ofApp.h"
#include "b2Contact.h"

vector<ofPolyline> importImage(const string& path){
    ofImage image;
    std::vector<ofPolyline> poly;
    
    if (!image.load(path))
    {
        throw std::invalid_argument(path);
    }
    
    ofxCv::ContourFinder contourFinder;
    contourFinder.setMinAreaRadius(0);
    contourFinder.setMaxAreaRadius(100000); //1000 max
    contourFinder.setThreshold(100);
    contourFinder.setInvert(true);
    contourFinder.setFindHoles(false);
    contourFinder.findContours(image);
    
    for (int i = 0 ; i < contourFinder.getPolylines().size(); i++){
        ofPolyline tempPoly;
        tempPoly = contourFinder.getPolyline(i);
        tempPoly.addVertex(tempPoly.getVertices().at(0));
        poly.push_back(tempPoly);
    }
    return poly;
}
//--------------------------------------------------------------
void ofApp::setup() {
    
    ofSetLogLevel(OF_LOG_SILENT);
    
    worlds = new WorldsBox2d;
    worlds->setup(&inputButton);
    
    scene1 = new Scene1(worlds, "Map_test_portails_back.png");
    //scene1 = new Scene1(worlds, "map_saut.jpg");

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
    
    std::vector<ofPolyline>  platforms = importImage("Map_test_portails_plateformes.png");
    //std::vector<ofPolyline>  platforms = importImage("map_plateform_saut.jpg");
    for (std::size_t i = 0; i < platforms.size() ; i++) {
        worlds->createPlatform(platforms[i]);
    }
    
    ////   Import Ladder   /////
    
    std::vector<ofPolyline>  ladders = importImage("Map_test_portails_echelles.png");
    //std::vector<ofPolyline>  ladders = importImage("map_echelle_saut.jpg");
    for (std::size_t i =0; i< ladders.size() ; i++) {
        worlds->createLadder(ladders[i]);
    }
    
    // Import blocs
    /*
    std::vector<ofPolyline> boxes = importImage("Map_prog_bloc_blanc.png");
    for (std::size_t i = 0; i < boxes.size() - 1; i++)
    {
        //worlds->createBox(boxes[i]);
    }
    
    // Import pickups
    std::vector<ofPolyline> pickups = importImage("Map_prog_pickup_blanc.png");
    for (std::size_t i = 0; i < pickups.size() - 1; i++)
    {
        //worlds->createPickup(pickups[i]);
    }*/
    
#ifdef USE_WIIMOTE
    wiiuse.addListener(this);
#endif
}

//--------------------------------------------------------------
void ofApp::update(){
    input();
    scene1->update();
    worlds->update(&inputButton);
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
    
    if (key == OF_KEY_LEFT || key == 'q')
    {
        inputButton[0].directionalCross[0] = true;
    }
    else if (key == OF_KEY_RIGHT || key == 'd')
    {
        inputButton[0].directionalCross[1] = true;    }
    else if (key == OF_KEY_UP || key == 'z')
    {
        inputButton[0].directionalCross[2] = true;
    }
    else if (key == OF_KEY_DOWN || key == 's')
    {
        inputButton[0].directionalCross[3] = true;
    }
    else if (key ==' '){
        inputButton[0].a = true;
    }
    else if (key == OF_KEY_LEFT_ALT){
        inputButton[0].b = !inputButton[0].b;
    }
    
    mapping.keyPressed(key);
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    for (int i = 0; i<worlds->avatars.size(); i++) {
        worlds->avatars[i]->keyReleased(key);
    }
    
    if (key == OF_KEY_LEFT || key == 'q')
    {
        inputButton[0].directionalCross[0] = false;    }
    else if (key == OF_KEY_RIGHT || key == 'd')
    {
        inputButton[0].directionalCross[1] = false;    }
    else if (key == OF_KEY_UP || key == 'z')
    {        
        inputButton[0].directionalCross[2] = false;
    }
    else if (key == OF_KEY_DOWN || key == 's')
    {
        inputButton[0].directionalCross[3] = false;    }
    else if (key ==' '){
        inputButton[0].a = false;
    }
    
    
    
    
    mapping.keyReleased(key);
    
    if (key == 'f')
    {
        std::cout << "Fullscreen!\n";
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
        if (aSprite == nullptr || bSprite == nullptr)return;
                
        if ( aSprite->physicalizedElement != nullptr)
        {
            aSprite->physicalizedElement->contactStart(e,e.a,bSprite);
        }
        if ( bSprite->physicalizedElement != nullptr)
        {
            bSprite->physicalizedElement->contactStart(e,e.b,aSprite);
        }

    }
}

void ofApp::contactEnd(ofxBox2dContactArgs &e)
{
    if (e.a != nullptr && e.b != nullptr)
    {
        dataSprite* aSprite = (dataSprite*)e.a->GetBody()->GetUserData();
        dataSprite* bSprite = (dataSprite*)e.b->GetBody()->GetUserData();
        

        if (aSprite == nullptr || bSprite == nullptr)return;
        
        if (aSprite->physicalizedElement != nullptr)
        {
            aSprite->physicalizedElement->contactEnd(e,e.a,bSprite);
        }
        if (bSprite->physicalizedElement != nullptr)
        {
            bSprite->physicalizedElement->contactEnd(e,e.b,aSprite);
        }
    }
}
#ifdef CUSTOM_BOX2D_TIM
void ofApp::PreSolve(ofxBox2dPreContactArgs &e)
{
    if (e.a != nullptr && e.b != nullptr)
    {
        dataSprite* aSprite = (dataSprite*)(e.a->GetBody()->GetUserData());
        dataSprite* bSprite = (dataSprite*)(e.b->GetBody()->GetUserData());
        
        if (aSprite == nullptr || bSprite == nullptr)
        {
            return;
        }
        
        if (aSprite->physicalizedElement != nullptr)
        {
            aSprite->physicalizedElement->PreSolve(e.a,bSprite,e);
        }
        
        if (bSprite->physicalizedElement != nullptr)
        {
            bSprite->physicalizedElement->PreSolve(e.b,aSprite,e);
        }
    }

}

void ofApp::PostSolve(ofxBox2dPostContactArgs &e)
{
    if (e.a != nullptr && e.b != nullptr && e.impulse != nullptr)
    {
        dataSprite* aSprite = (dataSprite*)(e.a->GetBody()->GetUserData());
        dataSprite* bSprite = (dataSprite*)(e.b->GetBody()->GetUserData());
        
        if (aSprite == nullptr || bSprite == nullptr)
        {
            return;
        }
        
        if (aSprite->physicalizedElement != nullptr)
        {
            aSprite->physicalizedElement->PostSolve(e.a,bSprite, e.impulse);
        }
        
        if (bSprite->physicalizedElement != nullptr)
        {
            bSprite->physicalizedElement->PostSolve(e.b,aSprite, e.impulse);
        }
    }
}
#endif //CUSTOM_BOX2D_TIM

void ofApp::input() {
    
#ifdef USE_WIIMOTE
    wiiuse.update();
#endif
    
    
    bool temp[2] = {false, false};
    
    if (ofxGLFWJoystick::one().getAxisValue(0, 0) > 0.5 || ofxGLFWJoystick::one().getAxisValue(0, 0) < -0.5) {
        if (ofxGLFWJoystick::one().getAxisValue(0, 0)>0) {
            temp[1] = true;
        }
        else {
            temp[0] = true;
        }
    }
    
    ofxGLFWJoystick::one().update();
    /*
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
    }*/
}

#ifdef USE_WIIMOTE
void ofApp::onWiiuseControlEvent(ofxWiiuseControlEventArgs& args)
{
    switch (args.second)
    {
            
    }
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
            
        default:
            break;
            
    }
}

void ofApp::onWiiuseMotionEvent(ofxWiiuseMotionEventArgs& args)
{
    
}

void ofApp::onWiiuseIRTrackingEvent(ofxWiiuseIRTrackingEventArgs& args)
{
}

#endif

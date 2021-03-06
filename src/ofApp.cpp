#include "ofApp.h"
#include "b2Contact.h"


//--------------------------------------------------------------
void ofApp::setup() {
    
    for (int i= 0; i<nbFace; i++) {
        faces[i].idFace=i;
    }
    ofSetLogLevel(OF_LOG_SILENT);
    
    worlds = new WorldsBox2d;
    worlds->setup();
    worlds->world.enableEvents();
    worlds->world.getWorld();
    
    Scene1Def def;
    def._spritesSolide = &spritesSolide;
    def._spritesLight = &spritesLight;
    def.worldsBox2d = worlds;
    def.background_name = "Map_test_portails_back.png";
    def.plaforms_name = "Map_test_portails_plateformes.png";
    


    generateFaces();
    def.faces = faces;

    ////   Import Platform   /////
    worlds->platforms.clear();
    
    imageTemp.load("Map_test_portails_plateformes.png");
    std::vector<ofPolyline>  platforms = importImage(imageTemp.getTexture());
    for (std::size_t i = 0; i < platforms.size() ; i++) {
        worlds->createPlatform(platforms[i], Category::PLATFORM);
    }
    
    imageTemp.load("Map_plateformes.png");
    //ofDisableArbTex();
    ofEnableArbTex(); // <-- Very Important
    for (int faceNb = 0; faceNb < nbFace; faceNb++) {
        for(int site = 0; site < 2; site++){
            
            fillMatrix( &faces[faceNb], site);
            layerToFace(imageTemp.getTexture());
            FboTemp.allocate(imageTemp.getWidth(), imageTemp.getHeight(),GL_RGBA);
            FboTemp.begin();
            ofClear(0,0, 0, 0);
            ofBackground(ofColor::white);
            int unit = 35;
            fboFace.getTexture().drawSubsection(320, 320 - unit , 320, unit, 320, 320 - unit);
            fboFace.getTexture().drawSubsection(320, 320*2 , 320, unit, 320, 320*2);
            fboFace.getTexture().drawSubsection(320 - unit, 320  , unit,320 , 320 - unit, 320 );
            fboFace.getTexture().drawSubsection(320*2, 320 , unit, 320, 320*2, 320);
            FboTemp.end();
            std::vector<ofPolyline>  platforms2 = importImage(FboTemp.getTexture());
            for (std::size_t i = 0; i < platforms2.size() ; i++) {
                
                for (int j=0; j<platforms2[i].getVertices().size(); j++) {
                    platforms2[i].getVertices()[j]= platforms2[i].getVertices()[j] - ofVec2f(320, 320) + faces[faceNb].rect.position;
                }
                if (site==0) {
                    worlds->createPlatform(platforms2[i], Category::PLATFORM_1);

                }else{
                    worlds->createPlatform(platforms2[i], Category::PLATFORM_2);

                }
            }

        }
    }
    
    ////   Import Ladder   /////
    imageTemp.load("Map_test_portails_echelles.png");
    std::vector<ofPolyline>  ladders = importImage(imageTemp.getTexture());
    for (std::size_t i =0; i< ladders.size() ; i++) {
        worlds->createLadder(ladders[i]);
    }
    

    worlds->createPortal(faces);
    
    
    
    {AvatarDef *avatarDef = new AvatarDef();
        avatarDef->world = worlds;
        avatarDef->positionInit=ofVec2f(2*366.899, 2*490.55);
        avatarDef->s= &inputButton[0];
        avatarDef->face = &faces[4];
        avatarDef->create();
        spritesSolide.push_back(static_cast<SpriteObj*>(avatarDef));
        spritesLight.push_back(static_cast<SpriteObj*>(avatarDef));
    }
    
    /*{ObjBlockDef *block = new ObjBlockDef();
        block->world=worlds;
        block->positionInit =ofVec2f(1204.45, 336.191);
        block->face =&faces[11];
        block->create();
        sprites.push_back(static_cast<SpriteObj*>(block));
        spritesSolide.push_back(static_cast<SpriteObj*>(block));}*/
    
    {ObjPlatforMoveDef *block = new ObjPlatforMoveDef();
        block->world=worlds;
        block->positionInit =ofVec2f(2*1204.45, 2*336.191);
        block->face =&faces[11];
        block->vitesse = ofVec2f(-20, 0);
        block->create();
        sprites.push_back(static_cast<SpriteObj*>(block));
        spritesSolide.push_back(static_cast<SpriteObj*>(block));}
    
    
    {
        ObjPickupDef *pkup = new ObjPickupDef();
        pkup->world = worlds;
        pkup->positionInit = ofVec2f(2*1204.45, 2*346.191);
        pkup->face = & faces[11];
        pkup->create();
        //spritesSolide.push_back(static_cast<SpriteObj*>(pkup));
        spritesLight.push_back(static_cast<SpriteObj*>(pkup));
        
    }
   
    
    for (int i = 0; i< 0; i++) {
        for (int j = 0; j<0; j++) {
            ObjPickupDef *pkup = new ObjPickupDef();
            pkup->world = worlds;
            pkup->positionInit = ofVec2f(102+20+48 + (320+48)*i, 80 + (320+48)*j);
            pkup->face = & faces[i+1 + j*10];
            pkup->create();
            spritesSolide.push_back(static_cast<SpriteObj*>(pkup));
            spritesLight.push_back(static_cast<SpriteObj*>(pkup));
            pkup = new ObjPickupDef();
            pkup->world = worlds;
            pkup->positionInit = ofVec2f(102+40+48 + (320+48)*i, 80 + (320+48)*j);
            pkup->face = & faces[i+1 + j*10];
            pkup->create();
            spritesSolide.push_back(static_cast<SpriteObj*>(pkup));
            spritesLight.push_back(static_cast<SpriteObj*>(pkup));
        }
        
    }

    
    /*ObjMushroomDef *objMushroomDef = new ObjMushroomDef();
    objMushroomDef->world= worlds;
    objMushroomDef->positionInit = ofVec2f(968, 440);
    objMushroomDef->face = &faces[10];
    objMushroomDef->create();
    sprites.push_back(static_cast<SpriteObj*>(objMushroomDef));
    spritesSolide.push_back(static_cast<SpriteObj*>(objMushroomDef));
    
    
    {ObjTrampolineDef *block = new ObjTrampolineDef();
    block->world=worlds;
    block->positionInit =ofVec2f(774.251, 552.55);
    block->face =&faces[8];
    block->create();
    sprites.push_back(static_cast<SpriteObj*>(block));
    spritesSolide.push_back(static_cast<SpriteObj*>(block));}
    
    {ObjBlockDef *block = new ObjBlockDef();
    block->world=worlds;
    block->positionInit =ofVec2f(1145.4, 292.062);
    block->face =&faces[11];
    block->create();
    sprites.push_back(static_cast<SpriteObj*>(block));
    spritesSolide.push_back(static_cast<SpriteObj*>(block));}
    
    {ObjBlockDef *block = new ObjBlockDef();
        block->world=worlds;
        block->positionInit =ofVec2f(1204.45, 336.191);
        block->face =&faces[11];
        block->create();
        sprites.push_back(static_cast<SpriteObj*>(block));
        spritesSolide.push_back(static_cast<SpriteObj*>(block));}
    
    {ObjBlockDef *block = new ObjBlockDef();
        block->world=worlds;
        block->positionInit =ofVec2f(1177.5, 484.19);
        block->face =&faces[12];
        block->create();
        sprites.push_back(static_cast<SpriteObj*>(block));
        spritesSolide.push_back(static_cast<SpriteObj*>(block));}
    
    
    // Avatar
    {AvatarDef *avatarDef = new AvatarDef();
    avatarDef->world = worlds;
    avatarDef->positionInit=ofVec2f(801.1, 434.474);
    avatarDef->s= &inputButton[0];
    avatarDef->face = &faces[8];
    avatarDef->create();
    spritesSolide.push_back(static_cast<SpriteObj*>(avatarDef));
        spritesLight.push_back(static_cast<SpriteObj*>(avatarDef));}
    
    
    {AvatarDef *avatarDef = new AvatarDef();
        avatarDef->world = worlds;
        avatarDef->positionInit=ofVec2f(337.997, 562.55);
        avatarDef->s= &inputButton[1];
        avatarDef->face = &faces[4];
        avatarDef->create();
        spritesSolide.push_back(static_cast<SpriteObj*>(avatarDef));
        spritesLight.push_back(static_cast<SpriteObj*>(avatarDef));
    }
    
    ///    ObjPickupDef
    {ObjPickupDef *pkup = new ObjPickupDef();
        pkup->world = worlds;
        pkup->positionInit = ofVec2f(816, 474);
        pkup->face = & faces[8];
        pkup->create();
        //b2Filter tempFilter = pkup->getFilter();
        //tempFilter.categoryBits = 0x0100;
        //tempFilter.maskBits = tempFilter.maskBits | 0x0100;
        //pkup->setFilter(tempFilter);
        //pkup->layerId = 6;
        spritesSolide.push_back(static_cast<SpriteObj*>(pkup));
        spritesLight.push_back(static_cast<SpriteObj*>(pkup));}

    {ObjPickupDef *pkup = new ObjPickupDef();
        pkup->world = worlds;
        pkup->positionInit = ofVec2f(196, 356);
        pkup->face = & faces[1];
        pkup->create();
        spritesSolide.push_back(static_cast<SpriteObj*>(pkup));
        spritesLight.push_back(static_cast<SpriteObj*>(pkup));}
    
    {ObjPickupDef *pkup = new ObjPickupDef();
    pkup->world = worlds;
    pkup->positionInit = ofVec2f(164, 452);
    pkup->face = & faces[2];
    pkup->create();

    spritesSolide.push_back(static_cast<SpriteObj*>(pkup));
    spritesLight.push_back(static_cast<SpriteObj*>(pkup));}
    
    {ObjPickupDef *pkup = new ObjPickupDef();
        pkup->world = worlds;
        pkup->positionInit = ofVec2f(985.358, 452.69);
        pkup->face = & faces[10];
        pkup->create();
        pkup->categoryBits= Category::OBJ_top;
        pkup->pkup->setFilter(Category::CLONE | Category::OBJ_top | Category::MUSHROOM_top);
        pkup->layerIni = pkup->layerId = 6;
        spritesSolide.push_back(static_cast<SpriteObj*>(pkup));
        //spritesLight.push_back(static_cast<SpriteObj*>(pkup));
    }
    
    {ObjPickupDef *pkup = new ObjPickupDef();
        pkup->world = worlds;
        pkup->positionInit = ofVec2f(500, 244);
        pkup->face = & faces[5];
        pkup->create();

        spritesSolide.push_back(static_cast<SpriteObj*>(pkup));
        spritesLight.push_back(static_cast<SpriteObj*>(pkup));}
    
    {ObjPickupDef *pkup = new ObjPickupDef();
        pkup->world = worlds;
        pkup->positionInit = ofVec2f(708, 244);
        pkup->face = & faces[7];
        pkup->create();

        spritesSolide.push_back(static_cast<SpriteObj*>(pkup));
        spritesLight.push_back(static_cast<SpriteObj*>(pkup));}

     */
     /*{ObjPickupDef *pkup = new ObjPickupDef();
        pkup->world = worlds;
        pkup->positionInit = ofVec2f(284, 524);
        pkup->face = & faces[4];
        //pkup->create();

        spritesSolide.push_back(static_cast<SpriteObj*>(pkup));
        spritesLight.push_back(static_cast<SpriteObj*>(pkup));}*/
    
    
    ofAddListener(worlds->world.contactStartEvents, this, &ofApp::contactStart);
    ofAddListener(worlds->world.contactEndEvents, this, &ofApp::contactEnd);
    
    
    scene1 = new Scene1(def);
    mapping.registerFboSource(scene1);
    mapping.setup();
    
#ifdef CUSTOM_BOX2D_TIM
    ofAddListener(worlds->world.PostSolveEvents, this, &ofApp::PostSolve);
    ofAddListener(worlds->world.PreSolveEvents, this, &ofApp::PreSolve);
#endif // CUSTOM_BOX2D_TIM
    
    
#ifdef USE_WIIMOTE
    wiiuse.addListener(this);
#endif
    
    ofxGLFWJoystick::one().printJoystickList();

}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString((int)ofGetFrameRate()));
    //input();
#ifdef USE_WIIMOTE
    wiiuse.update();
#endif
    scene1->update();
    if (!worlds->isThreadRunning()) {
        worlds->update();
        worlds->startThread();
    }else cout << "ATTENTION BOX2D RAM" << endl;
    mapping.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //scene1->draw();
    //ofBackground(ofColor::black);
    mapping.draw();
    //imageTemp.draw(0, 0);
    //FboTemp.draw(0,0);
    //fboFace.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    for (int i = 0; i<worlds->avatars.size(); i++) {
        //worlds->avatars[i]->keyPressed(key);
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
    
    if (key == 'm') {
        //tempI++;
        //cout << "tempI: " << tempI << endl;
        //cout << "position avatar: " << sprites[sprites.size()-1]->world->avatars[0]->getPosition() << endl;
        //cout << "top avatar: " << sprites[sprites.size()-1]->face->idFace << endl;
        
        cout << " [0]:"  << spritesSolide[0]->getViewPoint() << " [1]:" << spritesSolide[1]->getViewPoint()<<  endl;
        AvatarDef* a  = static_cast<AvatarDef*>(spritesSolide[0]);
        cout << " [0] posision:" << a->a->getPosition() << endl;
        ObjPlatforMoveDef* pM = static_cast<ObjPlatforMoveDef*>(spritesSolide[1]);
        cout << "[1] vitesse: " << pM->pM->getVelocity() << "   "<<pM->vitesse << endl;
        pM->pM->setVelocity(ofVec2f(-20, 0));
    }
    
    //mapping.keyPressed(key);
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    
    for (int i = 0; i<worlds->avatars.size(); i++) {
        //worlds->avatars[i]->keyReleased(key);
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
    
    
    //mapping.keyReleased(key);
    
    if (key == 'f')
    {
        std::cout << "Fullscreen!\n";
        fullscreen = !fullscreen;
        ofSetFullscreen(fullscreen);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    mapping.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mapping.mousePressed(x, y, button);
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

    
    ofxGLFWJoystick::one().update();

    for (int i = 0; i<4; i++) {
        inputButton[0].directionalCross[i] = false;
    }
    
    
    if (ofxGLFWJoystick::one().getAxisValue(0, 0) > 0.5 || ofxGLFWJoystick::one().getAxisValue(0, 0) < -0.5) {
        if (ofxGLFWJoystick::one().getAxisValue(0, 0)>0) {
            
            inputButton[0].directionalCross[1] = true;
        }
        else {
            inputButton[0].directionalCross[0] = true;
        }
    }

    if (ofxGLFWJoystick::one().getAxisValue(1, 0) > 0.5 || ofxGLFWJoystick::one().getAxisValue(1, 0) < -0.5) {
        if (ofxGLFWJoystick::one().getAxisValue(1, 0)>0) {

            inputButton[0].directionalCross[3] = true ;
        }
        else {
            inputButton[0].directionalCross[2] = true ;

        }
    }
    
    inputButton[0].a = ofxGLFWJoystick::one().getButtonValue(11, 0);
    inputButton[0].b = ofxGLFWJoystick::one().getButtonValue(13, 0);
    
    
    /* for (int joystickID = 0; joystickID < 1; joystickID++) {
     if (inputButton[joystickID].a != ofxGLFWJoystick::one().getButtonValue(11, joystickID)) {
     inputButton[joystickID].a = ofxGLFWJoystick::one().getButtonValue(11, joystickID);
     if (inputButton[joystickID].a) worlds->avatars[joystickID]->keyPressed(' ');
     else worlds->avatars[joystickID]->keyReleased(' ');
     }
     if (inputButton[joystickID][5] != ofxGLFWJoystick::one().getButtonValue(2, joystickID)) {
     inputButton[joystickID][5] = ofxGLFWJoystick::one().getButtonValue(2, joystickID);
     
     if (inputButton[joystickID][5])worlds->avatars[joystickID]->keyPressed(OF_KEY_LEFT_CONTROL);
     else worlds->avatars[joystickID]->keyReleased(OF_KEY_LEFT_CONTROL);
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
            //worlds->avatars[args.first - 1]->keyPressed(OF_KEY_LEFT);
            inputButton[args.first - 1].directionalCross[2] = true;
            break;
        }
        case OFXWIIUSE_BUTTON_UP_RELEASED:
        {
            //worlds->avatars[args.first - 1]->keyPressed(OF_KEY_LEFT);
            inputButton[args.first - 1].directionalCross[2] = false;
            break;
        }
        case OFXWIIUSE_BUTTON_DOWN_PRESSED:
        {
            //            worlds->avatars[args.first - 1]->keyPressed(OF_KEY_RIGHT);
            inputButton[args.first - 1].directionalCross[3] = true;
            break;
        }
            
        case OFXWIIUSE_BUTTON_DOWN_RELEASED:
        {
            //            worlds->avatars[args.first - 1]->keyReleased(OF_KEY_RIGHT);
            inputButton[args.first - 1].directionalCross[3] = false;
            break;
        }
        case OFXWIIUSE_BUTTON_LEFT_PRESSED:
        {
            //            worlds->avatars[args.first - 1]->keyPressed(OF_KEY_DOWN);
            inputButton[args.first - 1].directionalCross[0] = true;
            break;
        }
        case OFXWIIUSE_BUTTON_LEFT_RELEASED:
        {
            //            worlds->avatars[args.first - 1]->keyReleased(OF_KEY_DOWN);
            inputButton[args.first - 1].directionalCross[0] = false;
            break;
        }
        case OFXWIIUSE_BUTTON_RIGHT_PRESSED:
        {
            //            worlds->avatars[args.first - 1]->keyPressed(OF_KEY_UP);
            inputButton[args.first - 1].directionalCross[1] = true;
            break;
        }
        case OFXWIIUSE_BUTTON_RIGHT_RELEASED:
        {
            //            worlds->avatars[args.first - 1]->keyReleased(OF_KEY_UP);
            inputButton[args.first - 1].directionalCross[1] = false;
            break;
        }
        case OFXWIIUSE_BUTTON_ONE_PRESSED:
        {
            //            worlds->avatars[args.first - 1]->keyPressed(' ');
            inputButton[args.first - 1].a = true;
            break;
        }
        case OFXWIIUSE_BUTTON_ONE_RELEASED:
        {
            //            worlds->avatars[args.first - 1]->keyReleased(' ');
            inputButton[args.first - 1].a = false;
            break;
        }
        case OFXWIIUSE_BUTTON_TWO_PRESSED:
        {
            //            worlds->avatars[args.first - 1]->keyPressed(OF_KEY_LEFT_CONTROL);
            //inputButton[args.first - 1].b = true;
            inputButton[args.first - 1].b = !inputButton[args.first - 1].b;
            break;
        }
        case OFXWIIUSE_BUTTON_TWO_RELEASED:
        {
            //worlds->avatars[args.first - 1]->keyReleased(OF_KEY_LEFT_CONTROL);
            //inputButton[args.first - 1].b = false;
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

void ofApp::generateFaces()
{
    std::vector<std::vector<std::string>> f = readCSV(ofToDataPath("faces.csv"));
    for (std::size_t i = 0; i <nbFace*2; i += 2)
    {
        int id1 = std::atoi(f[i][0].c_str());
        float x1 = std::atof(f[i][3].c_str());
        float y1 = std::atof(f[i][4].c_str());
        float w1 = std::atof(f[i][5].c_str());
        float h1 = std::atof(f[i][6].c_str());
        
        int coef = 2;
        faces[id1].rect = ofRectangle(coef * x1,coef *  y1, coef * w1,coef *  h1);
        //cout << " id1 " << id1 << " id2 " << id2 << endl;
        faces[id1].matrix[0][0] = &faces[std::atoi(f[i][7].c_str())];
        faces[id1].matrix[0][1] = &faces[std::atoi(f[i][9].c_str())];
        faces[id1].matrix[0][2] = &faces[std::atoi(f[i][11].c_str())];
        faces[id1].matrix[0][3] = &faces[std::atoi(f[i][13].c_str())];
        faces[id1].matrix[0][4] = &faces[std::atoi(f[i][15].c_str())];
        faces[id1].matrix[0][5] = &faces[std::atoi(f[i][17].c_str())];
        faces[id1].matrix[0][6] = &faces[std::atoi(f[i][19].c_str())];
        faces[id1].matrix[0][7] = &faces[std::atoi(f[i][21].c_str())];
        faces[id1].matrix[0][8] = &faces[std::atoi(f[i][23].c_str())];
        
        faces[id1].matrix[1][0] = &faces[std::atoi(f[i+1][7].c_str())];
        faces[id1].matrix[1][1] = &faces[std::atoi(f[i+1][9].c_str())];
        faces[id1].matrix[1][2] = &faces[std::atoi(f[i+1][11].c_str())];
        faces[id1].matrix[1][3] = &faces[std::atoi(f[i+1][13].c_str())];
        faces[id1].matrix[1][4] = &faces[std::atoi(f[i+1][15].c_str())];
        faces[id1].matrix[1][5] = &faces[std::atoi(f[i+1][17].c_str())];
        faces[id1].matrix[1][6] = &faces[std::atoi(f[i+1][19].c_str())];
        faces[id1].matrix[1][7] = &faces[std::atoi(f[i+1][21].c_str())];
        faces[id1].matrix[1][8] = &faces[std::atoi(f[i+1][23].c_str())];
        
        faces[id1].matrixR[0].set(std::atoi(f[i][8].c_str()), std::atoi(f[i][14].c_str()), std::atoi(f[i][20].c_str()),
                                  std::atoi(f[i][10].c_str()), std::atoi(f[i][16].c_str()), std::atoi(f[i][22].c_str()),
                                  std::atoi(f[i][12].c_str()), std::atoi(f[i][18].c_str()), std::atoi(f[i][24].c_str()));
        faces[id1].matrixR[1].set(std::atoi(f[i+1][8].c_str()), std::atoi(f[i+1][14].c_str()), std::atoi(f[i+1][20].c_str()),
                                  std::atoi(f[i+1][10].c_str()), std::atoi(f[i+1][16].c_str()), std::atoi(f[i+1][22].c_str()),
                                  std::atoi(f[i+1][12].c_str()), std::atoi(f[i+1][18].c_str()), std::atoi(f[i+1][24].c_str()));
    }
    
}

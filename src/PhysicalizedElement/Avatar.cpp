//
//  Avatar.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//
#include "Avatar.h"
#include "Platform.h"
//#include "PickUp.h"
#include "../Portal.h"
std::vector<ofPoint> loadPoints(const std::string& file) {
    std::vector<ofPoint> pts;
    std::vector <std::string>  ptsStr = ofSplitString(ofBufferFromFile(file).getText(), ",");
    for (unsigned int i = 0; i < ptsStr.size(); i += 2) {
        float x = ofToFloat(ptsStr[i]);
        float y = ofToFloat(ptsStr[i+1]);
        pts.push_back(ofPoint(x, y));
    }
    return pts;
}
Avatar::Avatar(b2World* box2d)
{
    ////////// POLYGONE ///////////////////
    std::vector<ofPoint> pts = loadPoints("avatar.dat");
    polygon.addVertices(pts);
    //polygon.triangulatePoly();
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    //polygon.create(box2d);
    polygon.FilterDataObjet.categoryBits = 0x0001;
    polygon.FilterDataObjet.maskBits = 0x0001 | 0x0016 | 0x0032;
    polygon.FilterDataSide.categoryBits = 0x0002;
    polygon.FilterDataSide.maskBits = 0x0016;
    
    polygon.create(box2d, true);
    polygon.body->SetFixedRotation(true);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::AVATAR;
    data->physicalizedElement = this;
    /////////////// FOOT ///////////////
    
    moveInputX = 0.0f;
    setJumping(false);
    clicJump = false;
    cloneJump = false;
    modeDeplace = Deplacement::PLATFORM;
}
void Avatar::presUpdate()
{
    //collisionRect.set(polygon.getBoundingBox().getStandardized() + polygon.getPosition());
}
void Avatar::update(ofRectangle gravityWell)
{
    
    if (modeDeplace == Deplacement::PLATFORM)
    {
        move(moveInputX);
    }
    else
    {
        move(moveInputX, moveInputY);
    }
    //move(moveInputX);
    
    if (jumping)
    {
        polygon.setVelocity(polygon.getVelocity().x - (VarConst::coefFrotementAir * polygon.getVelocity().x/VarConst::speedAvatarMax), polygon.getVelocity().y);
    }
}
void Avatar::draw()
{
    ofSetColor(ofColor::blue);
    polygon.draw();
    ofSetColor(ofColor::white);

}
void Avatar::setPosition(ofVec2f vec)
{
    setPosition(vec.x, vec.y);
}
void Avatar::setPosition(int x, int y)
{
    polygon.setPosition(x, y);
    //collisionRect.setPosition(x, y);
}
void Avatar::move(float inputX)
{
    float speed = VarConst::speedAvatar;
    float speedMax = VarConst::speedAvatarMax;
    if (jumping)
    {
        
        speed = VarConst::speedAvatarAirControl;
        speedMax = VarConst::speedAvatarAirControlMax;
    }
    b2Vec2 impulse = speed * inputX * b2Vec2(1.0f, 0.0f);
    
    impulse *= (1 - std::min(std::abs(polygon.getVelocity().x), speedMax) / speedMax);
    //polygon.body->ApplyLinearImpulse(impulse, polygon.body->GetLocalCenter(), true);
    polygon.body->SetLinearVelocity(b2Vec2( inputX * speedMax, polygon.body->GetLinearVelocity().y));
}
void Avatar::move(float inputX,float inputY)
{
    float speed = VarConst::speedAvatar;
    float speedMax = VarConst::speedAvatarMax;
    b2Vec2 impulse;
    impulse.x = speed * inputX * 1.0f;
    impulse.y = speed * inputY * 1.0f;
    impulse *= (1 - std::min(polygon.getVelocity().length(), speedMax) / speedMax);
    polygon.body->ApplyLinearImpulse(impulse, polygon.body->GetLocalCenter(), true);
}
void Avatar::jump()
{
    cout << "jump:" <<  jumping << endl;
    if (!jumping)
    {
        setJumping(true);
        // allez zou, on vire l'inertie du joueur pour ne pas avoir d'elan
        //polygon.setVelocity(0, 0);
        // impulsion droite
        b2Vec2 impulseH = VarConst::impulseJumpAvatar * b2Vec2(0.0f, -1.0f);
        // impulsion latterale
        b2Vec2 impulseL = VarConst::impulseLateralJumpAvatar * moveInputX * b2Vec2(1.0f, 0.0f);
        //calcul de la direction et intensité du saut
        b2Vec2 impulse = impulseH + impulseL;
        impulse *= impulseH.Length() / impulse.Length();
        
        //si on ne saute pas droit, on attenue le saut pour ne pas avoir l'impression que le joueur accelere en sautant
        /*
         if (abs(moveInputX) > 0)
         {
         impulse *= VarConst::attenuationImpulseJump;
         }*/
        impulse = impulseH * (1 - polygon.getVelocity().x/VarConst::speedAvatarMax);
        
        polygon.body->ApplyLinearImpulse(impulseH, polygon.body->GetLocalCenter(), true);
    }
}
void Avatar::setJumping(bool _bool){
    jumping = _bool;
}
void Avatar::keyPressed(int key)
{
    if (key == OF_KEY_LEFT || key == 'q')
    {
        moveInputX = -1.0f;
    }
    else if (key == OF_KEY_RIGHT || key == 'd')
    {
        moveInputX = 1.0f;
    }
    else if (key == OF_KEY_UP || key == 'z')
    {
        moveInputY = -1.0f;
    }
    else if (key == OF_KEY_DOWN || key == 's')
    {
        moveInputY = 1.0f;
    }
    else if (key == OF_KEY_LEFT_CONTROL)
    {
        viewpoint = Viewpoint::MODE_PERSPECTIVE;
    }
    else if (key == ' ' && !clicJump)
    {
        clicJump = true;
        jump();
    }
    else if (key == 'r'){
        setJumping(0);
    }
}
void Avatar::keyReleased(int key)
{
    
    if (key == OF_KEY_LEFT || key == 'q')
    {
        moveInputX = 0.0f;
        
        if (!jumping || modeDeplace != Deplacement::PLATFORM) {
            polygon.setVelocity(0, polygon.getVelocity().y);
        }
        
    }
    else if (key == OF_KEY_RIGHT || key == 'd')
    {
        moveInputX = 0.0f;
        if (!jumping || modeDeplace != Deplacement::PLATFORM) {
            polygon.setVelocity(0, polygon.getVelocity().y);
        }
        
    }
    else if (key ==  OF_KEY_UP || key == 'z')
    {
        moveInputY = 0.0f;
        if (!jumping || modeDeplace != Deplacement::PLATFORM) {
            polygon.setVelocity(polygon.getVelocity().x,0);
        }
        
    }
    else if (key == OF_KEY_DOWN || key =='s')
    {
        moveInputY = 0.0f;
        if (!jumping|| modeDeplace != Deplacement::PLATFORM) {
            polygon.setVelocity(polygon.getVelocity().x,0) ;
        }
        
    }
    else if (key == OF_KEY_LEFT_CONTROL)
    {
        viewpoint = Viewpoint::MODE_ANGLE;
    }
    else if (key == ' ')
    {
        clicJump = false;
    }
}
void Avatar::contactStart(b2Fixture* _fixture, dataSprite* OtherSprite)
{
    
    b2Fixture * f = polygon.body->GetFixtureList()->GetNext()->GetNext();
    if (f == _fixture) {
        //cout << "Start Avatar DOWN " << ofGetElapsedTimef() <<endl;
        
        if (OtherSprite->sprite == Sprite::PLATFORM)
        {
            setJumping(false);
            if (!(abs(moveInputX) > 0))
            {
                polygon.setVelocity(0, polygon.getVelocity().y);
            }
        }
    }
    /*
    int oi = 0;
    for (b2Fixture * f = polygon.body->GetFixtureList(); f; f = f->GetNext()) {
        if (f == _fixture) {
            cout << _fixture << endl;
        }
        ++oi;
    }*/
    
    PhysicalizedElement::contactStart(_fixture ,OtherSprite);
    
    
}
void Avatar::contactEnd(b2Fixture* _fixture, dataSprite* OtherSprite)
{
    b2Fixture * f = polygon.body->GetFixtureList()->GetNext()->GetNext();
    if (f == _fixture) {
        //cout << "End Avatar DOWN " << ofGetElapsedTimef() <<endl;
    }
    
    PhysicalizedElement::contactEnd(_fixture, OtherSprite);
    
    if (OtherSprite->sprite == Sprite::PLATFORM)
    {
        //jumping = true; // bug pour jump mais doit etre remis pour le faite de tombŽ
    }
}
void Avatar::PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse)
{
    PhysicalizedElement::PostSolve(OtherSprite, impulse);
    
    if (OtherSprite->sprite == Sprite::PLATFORM && impulse->normalImpulses[0]< 1.f && impulse->normalImpulses[1]< 0.1 )
    {
        //cout << impulse->normalImpulses[0] << "  " << impulse->normalImpulses[1] << endl;

        //jumping = false;
        if (!(abs(moveInputX) > 0))
        {
            polygon.setVelocity(0, polygon.getVelocity().y);
        }
    }
    else if (OtherSprite->sprite == Sprite::PICKUP)
    {
        //static_cast<PickUp*>(OtherSprite->physicalizedElement)->setCollected();
    }
}

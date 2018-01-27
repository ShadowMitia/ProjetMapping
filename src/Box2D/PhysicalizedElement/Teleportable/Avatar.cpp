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
std::vector<ofPoint> loadPoints(const std::string& file)
{
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
    polygon.FilterDataObjet.maskBits = 0x0001 | 0x0016 | 0x0032 | 0x0128;
    polygon.FilterDataSide.categoryBits = 0x0002;
    polygon.FilterDataSide.maskBits = 0x0016;
    
    polygon.create(box2d, false);
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
    setMove(Deplacement::TOP);
    //polygon.body->SetGravityScale(0.0);
}
void Avatar::presUpdate()
{
}
void Avatar::update(Shift *s)
{
    moveInputX = s->directionalCross[1] - s->directionalCross[0];
    moveInputY = s->directionalCross[3] - s->directionalCross[2];
    (*this.*move)(moveInputX, moveInputY);
    if (jumping)
    {
        // polygon.setVelocity(polygon.getVelocity().x - (VarConst::coefFrotementAir * polygon.getVelocity().x/VarConst::speedAvatarMax), polygon.getVelocity().y);
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
}
void Avatar::movePlatform(float inputX, float inputY)
{
    float speed = VarConst::speedAvatar;
    float speedMax = VarConst::speedAvatarMax;
    if (jumping)
    {
        speed = VarConst::speedAvatarAirControl;
        speedMax = VarConst::speedAvatarAirControlMax;
    }
    
    if (inputX>0.f) {
        inputX=inputX;
    }else inputX=inputX;

    polygon.body->SetLinearVelocity(b2Vec2( inputX * speedMax,polygon.body->GetLinearVelocity().y));
}
void Avatar::moveNord(float inputX, float inputY)
{
    float speed = VarConst::speedAvatar;
    float speedMax = VarConst::speedAvatarMax;
    polygon.body->SetLinearVelocity(b2Vec2( inputX * speedMax, inputY * speedMax));
}
void Avatar::jump()
{
    if (!jumping)
    {
        setJumping(true);
        cloneJump = false;
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
void Avatar::setJumping(bool _bool)
{
    jumping = _bool;
}
void Avatar::keyPressed(int key)
{
    
     if (key == OF_KEY_LEFT_ALT)
    {
        if (viewpoint == Viewpoint::MODE_PERSPECTIVE) {
            viewpoint = Viewpoint::MODE_ANGLE;
        }
        else viewpoint = Viewpoint::MODE_PERSPECTIVE;
    }
    else if (key == ' ' && !clicJump)
    {
        clicJump = true;
        jump();
    }

}
void Avatar::keyReleased(int key)
{
    
    if (key == OF_KEY_LEFT_ALT)
    {
        //viewpoint = Viewpoint::MODE_ANGLE;
    }
    else if (key == ' ')
    {
        clicJump = false;
    }
}
void Avatar::contactStart(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite)
{
    if (abs(e.contact->GetManifold()->localPoint.x) != 0.2f && abs(e.contact->GetManifold()->localPoint.y) != 0.2f) {
        if (e.contact->GetManifold()->localNormal.y < 0.f) {
            polygon.tabCollision[2]++;
            setJumping(false);
            if (!(abs(moveInputX) > 0))
            {
                polygon.setVelocity(0, polygon.getVelocity().y);
            }
        }
        if (e.contact->GetManifold()->localNormal.y > 0.f) {
            polygon.tabCollision[1]++;
        }
        if (e.contact->GetManifold()->localNormal.x < 0.f) {
            polygon.tabCollision[4]++;
        }
        if (e.contact->GetManifold()->localNormal.x > 0.f) {
            polygon.tabCollision[3]++;
        }
    }
    //PhysicalizedElement::contactStart(_fixture ,OtherSprite);
}
void Avatar::contactEnd(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite)
{
    if (abs(e.contact->GetManifold()->localPoint.x) != 0.2f && abs(e.contact->GetManifold()->localPoint.y) != 0.2f) {
        if (e.contact->GetManifold()->localNormal.y < 0.f) {
            polygon.tabCollision[2]--;
            setJumping(true);
        }
        if (e.contact->GetManifold()->localNormal.y > 0.f) {
            polygon.tabCollision[1]--;
        }
        if (e.contact->GetManifold()->localNormal.x < 0.f) {
            polygon.tabCollision[4]--;
        }
        if (e.contact->GetManifold()->localNormal.x > 0.f) {
            polygon.tabCollision[3]--;
        }
    }
    if (OtherSprite->sprite == Sprite::PLATFORM)
    {
        //jumping = true; // bug pour jump mais doit etre remis pour le faite de tombŽ
    }
}
void Avatar::PostSolve(b2Fixture* _fixture,dataSprite* OtherSprite, const b2ContactImpulse* impulse)
{
    
}
void Avatar::PreSolve(b2Fixture* _fixture,dataSprite* OtherSprite,ofxBox2dPreContactArgs e)
{
    if (abs(e.contact->GetManifold()->localPoint.x) != 0.2f && abs(e.contact->GetManifold()->localPoint.y) != 0.2f) {
        if (e.contact->GetManifold()->localNormal.y < 0.f) {
            setJumping(false);
        }
    }
    
}

void Avatar::setMove(Deplacement _move){
    switch (_move) {
        case Deplacement::PLATFORM :
            cout << "PLATFORM" << endl;
            //move=&Avatar::movePlatform;
            move=&Avatar::moveNord;

            break;
        case Deplacement::TOP :
            cout << "TOP" << endl;
            move=&Avatar::moveNord;
    }
}
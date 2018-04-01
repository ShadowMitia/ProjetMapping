//
//  Avatar.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//
#pragma once
#include "Avatar.h"
#include "Platform.h"
//#include "PickUp.h"
#include "Portal.h"
#include "WorldsBox2d.h"
#include "Sprite.h"


/*
 Category bits:
 PLATFORM       : 0x0001
 PLATFORM-1     : 0x0002
 PLATFORM-2     : 0x0004
 PORTAL         : 0x0008
 LADDER         : 0x0010
 AVATAR         : 0x0020
 AVATAR-top     : 0x0040
 OBJ            : 0x0080
 OBJ-top        : 0x0100
 MUSHROOM-top   : 0x0200
 */

Avatar::Avatar(AvatarDef* _avatarDef)
{
    sprite = static_cast<SpriteObj*>(_avatarDef);
    _avatarDef->a = this;
    ////////// POLYGONE ///////////////////
    std::vector<ofPoint> pts = loadPoints("avatar.dat");
    polygon.addVertices(pts);
    
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    polygon.create(_avatarDef->world->world.getWorld(), true);
    polygon.body->SetFixedRotation(true);
    ////////////////////////////////////////////_avatarDef->setFilter(_avatarDef->filter);
    teleportableFilter.categoryBits = _avatarDef->categoryBits;
    
    cout << "1: " << _avatarDef->maskBits <<  "   " << teleportableFilter.maskBits<< endl;
    setFilter(_avatarDef->maskBits | Category::PLATFORM | Category::PLATFORM_1); // maskFilter
    cout << "2: " << teleportableFilter.maskBits << "  " << polygon.body->GetFixtureList()->GetFilterData().maskBits << endl;
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::AVATAR;
    data->physicalizedElement = this;
    /////////////// FOOT ///////////////
    
    
    
    //sensor.setPhysics(0, 0, 0);
    //sensor.setup(_avatarDef->world->world.getWorld(), 0, 0, 30);
    //sensor.body->GetFixtureList()->SetSensor(true);
    //sensor.setData(new dataSprite());
    //dataSprite* sentorData = (dataSprite*)sensor.getData();
    //sentorData->sprite = Sprite::sensorAVATAR;
    //sentorData->physicalizedElement = this;
    //b2Filter filterS;
    //filterS.categoryBits = Category::AVATAR;
    //filterS.maskBits = Category::OBJ;
    //sensor.body->GetFixtureList()->SetFilterData(filterS);
    b2Filter filter;
    filter.categoryBits = Category::AVATAR;
    filter.maskBits = Category::OBJ;
    polygon.body->GetFixtureList()->GetNext()->SetFilterData(filter);
    
    moveInputX = 0.0f;
    setJumping(false);
    clicJump = false;
    cloneJump = false;
    modeDeplace = Deplacement::PLATFORM;
    setMove(modeDeplace);
    ct = new coyoteTime(VarConst::coyoteTime,this);
    s=_avatarDef->s;
}
void Avatar::presUpdate()
{
    
}
void Avatar::update()
{
//////////////JUMP///////////////////
    sensor.setPosition(polygon.getPosition());
    if (s->a && !clicJump) {
        clicJump = true;
        jump();
    }
    if (!s->a && clicJump) {
        if (polygon.getVelocity().y < - VarConst::impulseJumpAvatarMIN) {
            polygon.setVelocity(polygon.getVelocity().x,  - VarConst::impulseJumpAvatarMIN);
        }
        clicJump = false;
    }
////////////////////////////////////
    if (!viewPointLock) {
        viewPoint = s->b;
        sprite->ViewPoint = viewPoint;
    }
    
    
    for (int i= 0; i<spriteForSensor.size(); ++i) {
        spriteForSensor[i]->viewPoint=viewPoint;
    }
    

    
    (*this.*preMove)(s);
    polygon.setVelocity(moveInputX, moveInputY);
    
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
/////////////// move avatar ///////////////
void Avatar::movePlatform(Shift *s)
{
    polygon.setRotation(0); // mettre a dans setMove();
    moveInputX = s->directionalCross[1] - s->directionalCross[0];
    moveInputY = polygon.body->GetLinearVelocity().y;

    float speed = VarConst::speedAvatar;
    float speedMax = VarConst::speedAvatarMax;
    if (jumping)
    {
        speed = VarConst::speedAvatarAirControl;
        speedMax = VarConst::speedAvatarAirControlMax;
    }
    moveInputX = moveInputX* speedMax;
    
    //polygon.body->SetLinearVelocity(b2Vec2( inputX * speedMax,polygon.body->GetLinearVelocity().y));
}
void Avatar::moveNord(Shift *s)
{
    float speed = VarConst::speedAvatar;
    float speedMax = VarConst::speedAvatarMax;
    moveInputX = (s->directionalCross[1] - s->directionalCross[0]) * speedMax;
    moveInputY = (s->directionalCross[2] - s->directionalCross[3]) * speedMax;

    //polygon.body->SetLinearVelocity(b2Vec2( -inputX * speedMax, -inputY * speedMax));
}

void Avatar::moveTop(Shift *s)
{
    float speed = VarConst::speedAvatar;
    float speedMax = VarConst::speedAvatarMax;
    float rotationMax = 1;
    polygon.setRotation(polygon.getRotation()+ (s->directionalCross[1] - s->directionalCross[0])*rotationMax);
    
    moveInputX = (s->directionalCross[3] - s->directionalCross[2]) * speedMax * sin(ofDegToRad( (int) abs(polygon.getRotation())%360) );
    moveInputY = (s->directionalCross[3] - s->directionalCross[2]) * speedMax * cos(ofDegToRad( (int) abs(polygon.getRotation())%360) ) ;
    cout << (int) abs(polygon.getRotation())%360 << " <<<<rotation "<< endl;

    //polygon.body->SetLinearVelocity(b2Vec2( + inputX * speedMax,  + inputY * speedMax));
}

void Avatar::moveSud(Shift *s)
{
    float speed = VarConst::speedAvatar;
    float speedMax = VarConst::speedAvatarMax;
    moveInputX = (s->directionalCross[1] - s->directionalCross[0]) * speedMax;
    moveInputY = (s->directionalCross[3] - s->directionalCross[2]) * speedMax;
    //polygon.body->SetLinearVelocity(b2Vec2( + inputX * speedMax,  + inputY * speedMax));
}



void Avatar::moveOuest(Shift *s)
{
    float speed = VarConst::speedAvatar;
    float speedMax = VarConst::speedAvatarMax;
    moveInputX = (s->directionalCross[2] - s->directionalCross[3]) * speedMax;
    moveInputY = (s->directionalCross[1] - s->directionalCross[0]) * speedMax;
    //polygon.body->SetLinearVelocity(b2Vec2( -inputY * speedMax, inputX * speedMax));
}
void Avatar::moveEst(Shift *s)
{
    float speed = VarConst::speedAvatar;
    float speedMax = VarConst::speedAvatarMax;
    moveInputX = (s->directionalCross[3] - s->directionalCross[2]) * speedMax;
    moveInputY = (s->directionalCross[0] - s->directionalCross[1]) * speedMax;
    //polygon.body->SetLinearVelocity(b2Vec2( inputY * speedMax, -inputX * speedMax));
}
void Avatar::moveLadder(Shift *s)
{
    moveInputX = s->directionalCross[1] - s->directionalCross[0];
    moveInputY = s->directionalCross[3] - s->directionalCross[2];
    float speed = VarConst::speedAvatar;
    float speedMax = VarConst::speedAvatarMax;
    moveInputX = moveInputX * speedMax;
    //if ((s->directionalCross[3] - s->directionalCross[2])==0) moveInputY = polygon.body->GetLinearVelocity().y;
    if (clicJump) { // je ne suis pas sur de cette thechnique
         moveInputY = polygon.body->GetLinearVelocity().y;
    }
}
void Avatar::setMove(Deplacement _move)
{
    switch (_move) {
        case Deplacement::PLATFORM :
            //cout << "PLATFORM" << endl;
            modeDeplace = Deplacement::PLATFORM;
            preMove=&Avatar::movePlatform;
            //(this->sprite->setMouve(platform))
            //move=&Avatar::moveNord;
            break;
        case Deplacement::TOP :
            //cout << "Nord" << endl;
            modeDeplace = Deplacement::TOP;
            preMove=&Avatar::moveNord;
            preMove=&Avatar::moveTop;
            break;
        case Deplacement::DOWN :
            //cout << "Sud" << endl;
            modeDeplace = Deplacement::DOWN;
            preMove=&Avatar::moveSud;
            preMove=&Avatar::moveTop;
            break;
        case Deplacement::LEFT :
            //cout << "Ouest" << endl;
            modeDeplace = Deplacement::LEFT;
            preMove=&Avatar::moveOuest;
            preMove=&Avatar::moveTop;
            break;
        case Deplacement::RIGHT :
            //cout << "Est" << endl;
            modeDeplace = Deplacement::RIGHT;
            preMove=&Avatar::moveEst;
            preMove=&Avatar::moveTop;
            break;
        case Deplacement::LADDER:
            modeDeplace = Deplacement::LADDER;
            preMove=&Avatar::moveLadder;
    }
}
/////////////// jump avatar ///////////////
void Avatar::jump()
{
    if (!jumping)
    {
        setJumping(true);
        cloneJump = false;
        polygon.setVelocity(polygon.getVelocity().x, - VarConst::impulseJumpAvatarMAX);
    }
}
void Avatar::setJumping(bool _bool)
{
    jumping = _bool;
}
/////////////// collision avatar ///////////////
void Avatar::contactStart(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite)
{

    if (_fixture == polygon.body->GetFixtureList()->GetNext()) {
        cout << " Start  " << ofGetElapsedTimeMillis()<< endl;
        Teleportable* t = static_cast<Teleportable*>(OtherSprite->physicalizedElement);
        spriteForSensor.push_back(t);
        
    }
    
    
    //if (OtherSprite->sprite==Sprite::BLOCK) {
        if (e.contact->GetManifold()->localNormal.y == 1) {
            setJumping(false);
        }
    //}
    
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

    if (_fixture == polygon.body->GetFixtureList()->GetNext()) {
        cout << " end  " << ofGetElapsedTimeMillis()<< endl;
        Teleportable* t = static_cast<Teleportable*>(OtherSprite->physicalizedElement);
        for (int i = 0; i< spriteForSensor.size(); ++i) {
            if (t == spriteForSensor[i] ) {
                spriteForSensor.erase(spriteForSensor.begin()+i);
                i = spriteForSensor.size();
            }
        }
    }
    
    if (abs(e.contact->GetManifold()->localPoint.x) != 0.2f && abs(e.contact->GetManifold()->localPoint.y) != 0.2f) {
        if (e.contact->GetManifold()->localNormal.y < 0.f) {
            polygon.tabCollision[2]--;
            if (OtherSprite->sprite==Sprite::PLATFORM && modeDeplace!=Deplacement::LADDER) {
                ct->startThread();
            }
            
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
void coyoteTime::threadedFunction()
{
    time.reset();
    time.waitNext();
    a->setJumping(true);
}

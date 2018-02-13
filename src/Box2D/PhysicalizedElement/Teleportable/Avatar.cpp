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
#include "Portal.h"
#include "WorldsBox2d.h"

/*
 Category bits:
 PLATFORM : 0x0001
 PORTAL   : 0x0002
 LADDER   : 0x0004
 CLONE    : 0x0008
 AVATAR   : 0x0010
 BLOCK    : 0x0020
 PICKUP   : 0x0040
 MUSHROOM : 0x0080
 */

Avatar::Avatar(AvatarDef* _avatarDef)
{
    sprite = static_cast<SpriteObj*>(_avatarDef);
    _avatarDef->a = this;
    ////////// POLYGONE ///////////////////
    std::vector<ofPoint> pts = loadPoints("avatar.dat");
    polygon.addVertices(pts);
    
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    polygon.FilterDataObjet.categoryBits = 0x0010;
    polygon.FilterDataObjet.maskBits = 0x0001 | 0x0002 | 0x0004 | 0x0008 | 0x0010 | 0x0020 | 0x0040 | 0x0080;
    
    polygon.create(_avatarDef->world->world.getWorld(), false);
    polygon.body->SetFixedRotation(true);
    polygon.setFilterDataSide(polygon.FilterDataObjet);
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
    viewPoint = s->b;
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
            //move=&Avatar::moveNord;
            break;
        case Deplacement::TOP :
            //cout << "Nord" << endl;
            modeDeplace = Deplacement::TOP;
            preMove=&Avatar::moveNord;
            break;
        case Deplacement::DOWN :
            //cout << "Sud" << endl;
            modeDeplace = Deplacement::DOWN;
            preMove=&Avatar::moveSud;
            break;
        case Deplacement::LEFT :
            //cout << "Ouest" << endl;
            modeDeplace = Deplacement::LEFT;
            preMove=&Avatar::moveOuest;
            break;
        case Deplacement::RIGHT :
            //cout << "Est" << endl;
            modeDeplace = Deplacement::RIGHT;
            preMove=&Avatar::moveEst;
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
void Avatar::keyPressed(int key)
{
}
void Avatar::keyReleased(int key)
{
}
/////////////// collision avatar ///////////////
void Avatar::contactStart(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite)
{
    if (OtherSprite->sprite==Sprite::BLOCK) {
        if (e.contact->GetManifold()->localNormal.y == 1) {
            setJumping(false);
        }
    }
    
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

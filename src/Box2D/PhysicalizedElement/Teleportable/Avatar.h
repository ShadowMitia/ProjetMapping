//
//  Avatar.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//
#pragma once

#include "ofMain.h"
#include "Teleportable.h"
#include "shift.h"
#include "Sprite.h"
#include "Ladder.h"


enum class Deplacement { PLATFORM = 0, TOP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, PLATFORMLADDER, LADDER };
class Avatar;
class coyoteTime: public ofThread{
public:
    ofTimer time;
    Avatar* a;
    coyoteTime(uint64_t _time, Avatar* _a){
        a = _a;
        time.setPeriodicEvent(_time);
    }
    void threadedFunction();
};
class Avatar : public Teleportable {
public:
    ofxBox2dCircle sensor;
    Avatar(AvatarDef* _avatarDef);
    Shift *s;
    bool jumping;
    bool clicJump;
    bool cloneJump;
    Deplacement modeDeplace;
    LockLadder lockLadder;

    void presUpdate();
    void update();
    void draw() ;
    void setJumping(bool _bool);
    
    void setMove(Deplacement move);

private:
    
    float moveInputX;
    float moveInputY;
    coyoteTime* ct;
    void jump();
    
    void(Avatar::*preMove)(Shift *s);
    void movePlatform(Shift *s);
    void moveNord(Shift *s);
    void moveSud(Shift *s);
    void moveEst(Shift *s);
    void moveOuest(Shift *s);
    void moveLadder(Shift *s);
    
    virtual void contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    virtual void contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    virtual void PostSolve(b2Fixture* _fixture,dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;
    virtual void PreSolve(b2Fixture* _fixture,dataSprite* OtherSprite,ofxBox2dPreContactArgs e) override;
    
    
};

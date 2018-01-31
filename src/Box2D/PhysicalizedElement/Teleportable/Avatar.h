//
//  Avatar.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//
#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Teleportable.h"
#include "ofxGLFWJoystick.h"
#include "PhysicalizedElement.h"
#include "shift.h"


enum class Deplacement { PLATFORM, TOP, DOWN, LEFT, RIGHT, PLATFORMLADDER };
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
    Avatar(b2World* box2d);
    bool jumping;
    
    bool clicJump;
    bool cloneJump;
    Deplacement modeDeplace;
    bool tabSideClone[5];
    
    
private:
    float moveInputX;
    float moveInputY;
    coyoteTime* ct;
public:
    void(Avatar::*move)(float inputX, float inputY);
    void movePlatform(float inputX, float inputY);
    void moveCardinalPoint(float inputX, float inputY);
    void movePlatformPointSud(float inputX, float inputY);
    
    void moveNord(float inputX, float inputY);
    void moveSud(float inputX, float inputY);
    void moveEst(float inputX, float inputY);
    void moveOuest(float inputX, float inputY);

    void presUpdate();
    void update(Shift *s) ;
    void draw() ;
    void setPosition(ofVec2f vec);
    void setPosition(int x, int y);
    void setJumping(bool _bool);
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    void setMove(Deplacement move);
    
    virtual void contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    virtual void contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    virtual void PostSolve(b2Fixture* _fixture,dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;
    virtual void PreSolve(b2Fixture* _fixture,dataSprite* OtherSprite,ofxBox2dPreContactArgs e) override;
    
    
private:
    
    void jump();
};



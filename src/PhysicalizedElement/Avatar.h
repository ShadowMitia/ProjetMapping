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


class Avatar : public Teleportable {
public:
    bool jumping;

    Avatar(b2World* box2d);
    
    bool clicJump;
    bool cloneJump;
    Deplacement modeDeplace;
    
    
private:
    float moveInputX;
    float moveInputY;
    Viewpoint viewpoint = Viewpoint::MODE_ANGLE;
    
public:
    void presUpdate();
    void update(ofRectangle gravityWell) ;
    void draw() ;
    void setPosition(ofVec2f vec);
    void setPosition(int x, int y);
    void setJumping(bool _bool);
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    virtual void contactStart(b2Fixture* _fixture, dataSprite* OtherSprite) override;
    virtual void contactEnd(b2Fixture* _fixture, dataSprite* OtherSprite) override;
    virtual void PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;
    
private:
    void move(float inputX);
    void move(float inputX, float inputY);
    void jump();
};

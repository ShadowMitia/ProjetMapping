//
//  ObjPickup.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 09/02/2018.
//
//

#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Teleportable.h"

class ObjPickup: public Teleportable{
public:
    ObjPickup(b2World* box2d);
    void draw();

private:
    virtual void contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    virtual void contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    //virtual void PostSolve(b2Fixture* _fixture,dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;
    //virtual void PreSolve(b2Fixture* _fixture,dataSprite* OtherSprite,ofxBox2dPreContactArgs e) override;
};

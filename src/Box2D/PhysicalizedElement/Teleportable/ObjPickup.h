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
#include "Sprite.h"
class ObjPickup;
class deActive: public ofThread{
public:
    ofTimer time;
    ObjPickup* pckup;
    deActive(uint64_t _time, ObjPickup* _pckup){
        pckup = _pckup;
        time.setPeriodicEvent(_time);
    }
    void threadedFunction();
};
class ObjPickup: public Teleportable{
public:
    ObjPickup(ObjPickupDef* _objPickupDef);
    void draw();
    deActive* deactive;

private:
    
    virtual void contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    virtual void contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    //virtual void PostSolve(b2Fixture* _fixture,dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;
    //virtual void PreSolve(b2Fixture* _fixture,dataSprite* OtherSprite,ofxBox2dPreContactArgs e) override;
};

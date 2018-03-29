//
//  ObjBlock.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/02/2018.
//
//

#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Teleportable.h"
#include "AllSprite.h"

class ObjBlock;
class resteTime: public ofThread{
public:
    ofTimer time;
    ObjBlock* b;
    resteTime(uint64_t _time, ObjBlock* _b){
        b = _b;
        time.setPeriodicEvent(_time);
    }
    void threadedFunction();
};

class ObjBlock: public Teleportable{
public:
    
    ObjBlock(ObjBlockDef* _objBlockDef);
    void draw();
    resteTime *rT;
    
private:
    virtual void contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    virtual void contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    //virtual void PostSolve(b2Fixture* _fixture,dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;
    //virtual void PreSolve(b2Fixture* _fixture,dataSprite* OtherSprite,ofxBox2dPreContactArgs e) override;
};

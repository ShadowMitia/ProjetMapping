//
//  Clone.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/01/2018.
//
//

#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "Teleportable.h"
#include "PhysicalizedElement.h"

class Portal;
class CloneBox2d: public PhysicalizedElement{
public:
    
    int statut;
    int layer = 0;
    Teleportable* objSource;
    Portal* portalSource = nullptr;
    Portal* portalDestination = nullptr;
    

    CloneBox2d(Teleportable* _objSource, Portal* _portalSource, Portal* _portalDestination);
    ~CloneBox2d();
    void update();
    void create();
    void draw();
    
    void contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    void contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    
private:
    b2Filter tempFilter;
    bool portalView;
    void (CloneBox2d::*collisionFonction)();
    void collisionFonctionAvatar();
    void collisionFonctionOther();
    
    void (CloneBox2d::*contactStartFonction)(b2Fixture* _fixture, dataSprite* OtherSprite);
    void (CloneBox2d::*contactEndFonction)(b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactStartAvatar(b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactEndAvatar(b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactStartOther(b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactEndOther(b2Fixture* _fixture, dataSprite* OtherSprite);
    
    void PostSolve(b2Fixture* _fixture,dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;
    void PreSolve(b2Fixture* _fixture,dataSprite* OtherSprite,ofxBox2dPreContactArgs e) override;
    
    void (CloneBox2d::*delectClone)();
    void delectCloneAvatar();
    void delectCloneOther();

    ObjectGame polygon;
    ofPoint PositionObjSource;
    ofPoint PositionClone;
    bool lockTransfer = false;
    float matrixTrans[2];
    ofVec2f multyMatrix(ofVec2f v);
    
    bool ladderTouch = false;
    
};
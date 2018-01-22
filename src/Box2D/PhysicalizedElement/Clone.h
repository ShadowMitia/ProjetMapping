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
    Teleportable* objSource;
    Portal* portalSource = nullptr;
    Portal* portalDestination = nullptr;

    CloneBox2d(PhysicalizedElement* _objSource, Portal* _portalSource, Portal* _portalDestination);
    ~CloneBox2d();
    void update();
    void create();
    void draw();
    
    void contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    void contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    
private:
    void (CloneBox2d::*collisionFonction)();
    void collisionFonctionAvatar();
    void collisionFonctionUnknown();
    void (CloneBox2d::*contactStartFonction)(b2Fixture* _fixture, dataSprite* OtherSprite);
    void (CloneBox2d::*contactEndFonction)(b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactStartAvatar(b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactEndAvatar(b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactStartUnknown(b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactEndUnknown(b2Fixture* _fixture, dataSprite* OtherSprite);
    void PostSolve(b2Fixture* _fixture,dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;
    void PreSolve(b2Fixture* _fixture,dataSprite* OtherSprite,ofxBox2dPreContactArgs e) override;
    ObjectGame polygon;
    ofPoint PositionObjSource;
    ofPoint PositionClone;
    
    
};
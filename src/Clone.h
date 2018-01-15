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
    
    void contactStart(b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactEnd(b2Fixture* _fixture, dataSprite* OtherSprite);
    
private:
    void (*collisionFonction)();
    //void collisionFonctionAvatar();
    void collisionFonctionUnknown();
    ObjectGame polygon;
    ofPoint PositionObjSource;
    ofPoint PositionClone;
};
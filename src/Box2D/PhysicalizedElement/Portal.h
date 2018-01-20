//
//  Portal.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 23/07/2017.
//
//
#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "Teleportable/Teleportable.h"
#include "Clone.h"
#include "utils.h"

enum class ConditionOutput{VerticalLeft,VerticalRight, HorizontalTop, HorizontalDown};
enum class PortalDirection{leftDirection, rightDirection, topDirection, downDirection};

class WorldsBox2d;

class Portal:public PhysicalizedElement{
public:
    
    void (*nullFunction)(CloneBox2d*);
    Portal *linkedPortal[2];
    bool(*conditionFunction)(ofVec2f, CloneBox2d*);
    b2World* getb2World();
    ofRectangle portalRect;
    
    Portal(ofRectangle _portal, WorldsBox2d * _worldsBox2d,PortalDirection _direction,ConditionOutput _Output);
    void draw();
    void linke(Portal * _1, Portal* _2);
    ofVec2f getPosition();
    ofVec2f getObjPosition(ofVec2f p){
        return  portalRect.position - p;
    }
    
private:
    WorldsBox2d* worldsBox2d;
    ofxBox2dPolygon polygon;
    std::vector< CloneBox2d *> clones;
    
    void contactStart(b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactEnd(b2Fixture* _fixture, dataSprite* OtherSprite);
};


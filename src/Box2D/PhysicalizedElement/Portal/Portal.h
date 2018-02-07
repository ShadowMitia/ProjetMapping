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
#include "Avatar.h"
#include "Face.h"

enum class ConditionOutput{VerticalLeft,VerticalRight, HorizontalTop, HorizontalDown, CornerTopLeft, CornerTopRight, CornerDownLeft, CornerDownRight};
//enum class PortalDirection{leftDirection, rightDirection, topDirection, downDirection};

class WorldsBox2d;

class Portal:public PhysicalizedElement{
public:
    
    ofVec2f orient;
    Deplacement direct;
    Face* face;
    Portal *linkedPortal[2];
    ofRectangle portalRect;
    b2World* getb2World();
    
    Portal(ofRectangle _portal, WorldsBox2d * _worldsBox2d,Deplacement _direction,ConditionOutput _Output,Face* _face);
    
    void (*nullFunction)(CloneBox2d*);
    bool(*conditionFunction)(ofVec2f, CloneBox2d*);
    void linke(Portal * _1, Portal* _2);
    ofVec2f getPosition();
    const ofVec2f (Portal::*getObjPosition)(ofVec2f p);
    void draw();
    
private:
    
    WorldsBox2d* worldsBox2d;
    ofxBox2dPolygon polygon;
    std::vector< CloneBox2d *> clones;
    void contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite);
    
    const ofVec2f getObjPositionLeft(ofVec2f p){
        return  portalRect.getCenter() - p;
    }
    
    const ofVec2f getObjPositionRight(ofVec2f p){
        return  portalRect.getCenter()  - p;
    }
    
};

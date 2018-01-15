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
#include "PhysicalizedElement/Teleportable.h"
#include "Clone.h"

enum class ConditionOutput{VerticalLeft,VerticalRight, Horizontal};
enum class PortalDirection{leftDirection, rightDirection};
class WorldsBox2d;

class Portal:public PhysicalizedElement{
public:
    Portal *linkedPortal[2];
    ofVec2f(*directionFunction)(CloneBox2d*);
    bool(*conditionFunction)(float, CloneBox2d*);
    b2World* getb2World();
    ofRectangle portalRect;
    
    Portal(ofRectangle _portal, WorldsBox2d * _worldsBox2d,PortalDirection _direction,ConditionOutput _Output);
    void draw();
    void linke(Portal * _1, Portal* _2);
    ofVec2f getPosition();
    void tqdqet(){
        CloneBox2d * dqoih;
        conditionFunction(1.0,dqoih);
    };
private:
    WorldsBox2d* worldsBox2d;
    ofxBox2dPolygon polygon;
    std::vector< CloneBox2d *> clones;
    
    void contactStart(b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactEnd(b2Fixture* _fixture, dataSprite* OtherSprite);
};

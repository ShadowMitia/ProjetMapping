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

enum class Orientation { Horizontal, Vertical };
enum class PortalDirection { Left, Right };
class WorldsBox2d;

class Portal:public PhysicalizedElement{
public:
    Portal *linkedPortal[2];

    Portal(b2World* _box2d,ofRectangle _portal, WorldsBox2d * _worldsBox2d);
    void draw();
    b2World* getb2World();
    void contactStart(dataSprite* OtherSprite);
    void contactEnd(dataSprite* OtherSprite);
    void linke(Portal * _1, Portal* _2);
    ofVec2f getPosition();
    
private:
    ofRectangle portalRect;
    WorldsBox2d* worldsBox2d;
    b2World* box2d;
    ofxBox2dPolygon polygon;
    std::vector< CloneBox2d *> clones;

};

